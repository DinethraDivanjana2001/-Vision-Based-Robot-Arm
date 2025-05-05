#include <WiFi.h>
#include <ESP32Servo.h>
#include <WebServer.h>

const char* ssid     = "MSI_GF65";
const char* password = "Dinethrad";
WebServer server(80);


Servo servo1;
const int servoPin1 = 26;
const int n = 4;


int currentPositions[n] = {1500};
const int duration       = 2000;
const int updateInterval = 1;    // update int
double now_time          = 0;    // used for smoothMove()

void setup() {
  Serial.begin(9600);
  delay(100);

  connectToWiFi();

  servo1.setPeriodHertz(50);
  

  servo1.attach(servoPin1);

  server.on("/set_positions", handleSetPositions);
  server.begin();
  Serial.println("WebServer started.");
  

  moveToPositions(currentPositions);
}

void loop() {
  server.handleClient();

  }



void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}

void handleSetPositions() {
  if (server.hasArg("pos")) {
    String positionsArg = server.arg("pos");
    int newPositions[n];

    if (parsePositions(positionsArg, newPositions)) {
      smoothMove(servo1, currentPositions, newPositions, duration);

      for (int i = 0; i < n; i++) {
        currentPositions[i] = newPositions[i];
      }

      server.send(200, "text/plain", "Positions updated");
    } else {
      server.send(400, "text/plain", "Invalid position data");
    }
  } else {
    server.send(400, "text/plain", "Missing 'pos' parameter");
  }
}



bool parsePositions(String input, int positions[]) {
  int index      = 0;
  int startIndex = 0;
  int commaIndex;

  while ((commaIndex = input.indexOf(',', startIndex)) != -1 && index < 4) {
    positions[index++] = input.substring(startIndex, commaIndex).toInt();
    startIndex = commaIndex + 1;
  }

  if (index < 3 || startIndex >= input.length()) {
    return false;
  }

  positions[index++] = input.substring(startIndex).toInt();
  return true;
}


void moveToPositions(int positions[]) {
  servo1.writeMicroseconds(positions[0]);
  //servo2.writeMicroseconds(positions[1]);
  //servo3.writeMicroseconds(positions[2]);
  //servo4.writeMicroseconds(positions[3]);
}




void smoothMove(Servo &s1, Servo &s2, Servo &s3, Servo &s4,
                int start[], int end[], int durationMs) 
{
  int steps = durationMs / updateInterval; // number of interpolation steps

  float increments[4];
  for (int i = 0; i < 4; i++) {
    increments[i] = (float)(end[i] - start[i]) / steps;
  }

  for (int step = 0; step <= steps; step++) {
    int currentPos[4] = {
      start[0] + (int)(increments[0] * step),
      start[1] + (int)(increments[1] * step),
      start[2] + (int)(increments[2] * step),
      start[3] + (int)(increments[3] * step)
    };

    now_time = millis();
    while (millis() - now_time < updateInterval) {
      s1.writeMicroseconds(currentPos[0]);
      s2.writeMicroseconds(currentPos[1]);
      s3.writeMicroseconds(currentPos[2]);
      s4.writeMicroseconds(currentPos[3]);
    }
  }
