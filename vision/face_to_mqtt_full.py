import argparse, sys, time, json, cv2
import mediapipe as mp
import paho.mqtt.client as mqtt

BROKER_HOST  = "demo.thingsnode.cc"       
BROKER_PORT  = 1883                   
ACCESS_TOKEN = "pAwkmYYgG2RlUoVR6uSC"    
TOPIC        = "v1/devices/me/telemetry" 

FRAME_W, FRAME_H = 640, 480                            

ap = argparse.ArgumentParser(description="Face → MQTT publisher")
ap.add_argument("--cam", type=int, default=0, help="Webcam index (default 0)")
args = ap.parse_args()

mqttc = mqtt.Client("vision_publisher_full")
mqttc.username_pw_set(ACCESS_TOKEN)  

try:
    mqttc.connect(BROKER_HOST, BROKER_PORT, keepalive=30)
    mqttc.loop_start()
    print(f"MQTT connected to {BROKER_HOST}:{BROKER_PORT}")
except Exception as e:
    print("MQTT connect failed:", e)
    mqttc = None

cap = cv2.VideoCapture(args.cam, cv2.CAP_DSHOW)
cap.set(cv2.CAP_PROP_FRAME_WIDTH,  FRAME_W)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, FRAME_H)

if not cap.isOpened():
    print(f"Could not open camera index {args.cam}. Is it in use?")
    input("Press Enter to exit…")
    sys.exit(1)

print(f"Camera {args.cam} opened at {FRAME_W}×{FRAME_H}")

mp_face = mp.solutions.face_detection.FaceDetection(
    model_selection=0,
    min_detection_confidence=0.6
)

def publish(payload: dict):
    """Send JSON to MQTT if the connection is alive."""
    if mqttc:
        mqttc.publish(TOPIC, json.dumps(payload), qos=0, retain=False)
try:
    while True:
        ok, frame = cap.read()
        if not ok:
            print("Frame read failed — retrying …")
            time.sleep(0.1)
            continue

        rgb  = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        dets = mp_face.process(rgb).detections

        if dets:
            d = max(dets, key=lambda d: d.score[0])
            b = d.location_data.relative_bounding_box

            cx = b.xmin + b.width * 0.5
            cy = b.ymin + b.height * 0.5
            area = b.width * b.height

            payload = {"x": round(cx, 3), "y": round(cy, 3), "z": round(area, 3)}
            publish(payload)
            print("→ Published:", payload)

            x0, y0 = int(b.xmin * FRAME_W), int(b.ymin * FRAME_H)
            x1, y1 = int((b.xmin + b.width) * FRAME_W), int((b.ymin + b.height) * FRAME_H)
            cv2.rectangle(frame, (x0, y0), (x1, y1), (0, 255, 0), 2)

            label = f"x={payload['x']:.2f}  y={payload['y']:.2f}  z={payload['z']:.2f}"
            cv2.putText(frame, label, (x0, y0 - 10),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
        else:
            cv2.putText(frame, "No face",
                        (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 255), 2)

        cv2.imshow("Face-tracking monitor (Esc to quit)", frame)
        if cv2.waitKey(1) & 0xFF == 27:  # Esc key
            break

finally:
    cap.release()
    cv2.destroyAllWindows()
    if mqttc:
        mqttc.loop_stop()
        mqttc.disconnect()
    print("Closed cleanly")
