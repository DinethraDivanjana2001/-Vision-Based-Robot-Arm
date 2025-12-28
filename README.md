# 🤖 Vision-Based Robot Arm

<div align="center">

![Project Status](https://img.shields.io/badge/Status-Active-success)
![License](https://img.shields.io/badge/License-MIT-blue)
![Python](https://img.shields.io/badge/Python-3.8+-blue.svg)
![Arduino](https://img.shields.io/badge/Arduino-ESP32-00979D.svg)

*An intelligent robotic arm system that leverages computer vision for real-time object detection, face tracking, and autonomous manipulation tasks.*

[Features](#-features) • [Architecture](#-system-architecture) • [Installation](#-installation) • [Usage](#-usage) • [Documentation](#-documentation)

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [System Architecture](#-system-architecture)
- [Hardware Components](#-hardware-components)
- [Software Stack](#-software-stack)
- [Installation](#-installation)
- [Usage Guide](#-usage-guide)
- [Project Structure](#-project-structure)
- [Implementation Details](#-implementation-details)
- [Communication Protocols](#-communication-protocols)
- [Control Algorithms](#-control-algorithms)
- [Applications](#-applications)
- [Future Enhancements](#-future-enhancements)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)
- [License](#-license)
- [Acknowledgments](#-acknowledgments)

---

## 🌟 Overview

The **Vision-Based Robot Arm** is an advanced mechatronic system that combines computer vision, real-time control algorithms, and IoT connectivity to create an intelligent robotic manipulation platform. This project demonstrates the integration of multiple technologies including:

- **Computer Vision**: Real-time face detection and tracking using OpenCV and MediaPipe
- **IoT Communication**: MQTT protocol for cloud-based telemetry and remote monitoring
- **Embedded Systems**: ESP32 microcontroller for servo control and sensor integration
- **Motion Control**: Smooth interpolation algorithms for natural robotic movements
- **Autonomous Operation**: Ultrasonic sensor-based object detection for pick-and-place tasks

The system is designed to be modular, scalable, and adaptable for various applications ranging from educational demonstrations to industrial automation prototypes.

---

## ✨ Features

### 🎯 Core Capabilities

- **Real-Time Face Detection & Tracking**
  - High-accuracy face detection using MediaPipe ML models
  - Haar Cascade classifier support for lightweight detection
  - Multi-face detection with confidence scoring
  - Bounding box visualization and coordinate extraction

- **Vision-Guided Servo Control**
  - 2-axis (pan-tilt) servo tracking system
  - Coordinate-to-angle mapping with interpolation
  - Smooth motion control with configurable speed
  - Target locking mechanism with visual feedback

- **IoT Integration**
  - MQTT-based telemetry publishing to cloud platforms
  - Real-time coordinate streaming (x, y, z)
  - Remote monitoring and data logging capabilities
  - Integration with ThingsBoard/ThingsNode IoT platforms

- **Autonomous Pick-and-Place**
  - Ultrasonic distance sensing for object detection
  - Pre-programmed motion sequences for manipulation tasks
  - 5-DOF (Degrees of Freedom) robotic arm control
  - Gripper mechanism for object handling

- **Advanced Motion Control**
  - Smooth servo interpolation for natural movements
  - Position-based control with microsecond precision
  - Synchronized multi-servo coordination
  - Configurable motion profiles and speeds

- **User Interface**
  - Real-time video feed with overlay graphics
  - On-screen telemetry display (coordinates, angles, status)
  - OLED display integration for standalone operation
  - Visual target indicators and status messages

---

## 🏗️ System Architecture

The system follows a modular architecture with three main layers:

```
┌─────────────────────────────────────────────────────────────┐
│                    PERCEPTION LAYER                          │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐      │
│  │   Camera     │  │  Ultrasonic  │  │    OLED      │      │
│  │   Module     │  │    Sensor    │  │   Display    │      │
│  └──────────────┘  └──────────────┘  └──────────────┘      │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│                   PROCESSING LAYER                           │
│  ┌──────────────────────────────────────────────────────┐   │
│  │  Computer Vision Pipeline (Python)                   │   │
│  │  • OpenCV Image Processing                           │   │
│  │  • MediaPipe Face Detection                          │   │
│  │  • Coordinate Extraction & Mapping                   │   │
│  │  • MQTT Publishing                                   │   │
│  └──────────────────────────────────────────────────────┘   │
│                            ↓                                 │
│  ┌──────────────────────────────────────────────────────┐   │
│  │  Embedded Controller (ESP32)                         │   │
│  │  • Servo Control Logic                               │   │
│  │  • Motion Interpolation                              │   │
│  │  • Sensor Data Processing                            │   │
│  │  • WiFi/Web Server                                   │   │
│  └──────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│                    ACTUATION LAYER                           │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐      │
│  │  5x Servo    │  │   Gripper    │  │  Robot Arm   │      │
│  │   Motors     │  │  Mechanism   │  │  Structure   │      │
│  └──────────────┘  └──────────────┘  └──────────────┘      │
└─────────────────────────────────────────────────────────────┘
```

### Communication Flow

1. **Vision Pipeline**: Camera captures frames → OpenCV/MediaPipe processes → Extracts coordinates
2. **Data Transmission**: Coordinates published via MQTT → Cloud platform receives telemetry
3. **Control Signal**: ESP32 receives commands → Calculates servo angles → Interpolates motion
4. **Actuation**: Servo motors execute movements → Robot arm tracks target/performs task

---

## 🔧 Hardware Components

### Required Components

| Component | Specification | Quantity | Purpose |
|-----------|--------------|----------|---------|
| **Microcontroller** | ESP32 Development Board | 1 | Main control unit with WiFi |
| **Servo Motors** | SG90/MG996R (180° range) | 5 | Joint actuation |
| **Camera** | USB Webcam (640×480 min) | 1 | Vision input |
| **Ultrasonic Sensor** | HC-SR04 | 1 | Distance measurement |
| **OLED Display** | SSD1306 (128×64) | 1 | Status display |
| **Power Supply** | 5V 3A adapter | 1 | Servo power |
| **Robot Arm Kit** | 5-DOF mechanical structure | 1 | Physical platform |
| **Connecting Wires** | Jumper wires | - | Connections |
| **Breadboard** | Standard size | 1 | Prototyping |

### Pin Configuration (ESP32)

```cpp
// Servo Connections
Servo 1 (Base Rotation):    GPIO 26
Servo 2 (Shoulder):          GPIO 4
Servo 3 (Elbow):             GPIO 13
Servo 4 (Wrist):             GPIO 15
Servo 5 (Gripper):           GPIO 2

// Sensor Connections
Ultrasonic Trigger/Echo:     GPIO 33
I2C SDA (OLED):              GPIO 21
I2C SCL (OLED):              GPIO 22
```

### Alternative Configurations

- **Arduino-based**: Compatible with Arduino Uno/Mega using Firmata protocol
- **Raspberry Pi**: Can run vision processing directly on Pi with camera module
- **Wireless Control**: ESP32 WiFi for remote operation via web interface

---

## 💻 Software Stack

### Python Dependencies

```
opencv-python >= 4.5.0      # Computer vision library
mediapipe >= 0.8.0          # ML-based face detection
paho-mqtt >= 1.6.0          # MQTT client
cvzone >= 1.5.0             # Computer vision utilities
pyfirmata >= 1.1.0          # Arduino communication
numpy >= 1.19.0             # Numerical operations
```

### Arduino/ESP32 Libraries

```cpp
ESP32Servo.h                // Servo control for ESP32
WiFi.h                      // WiFi connectivity
WebServer.h                 // HTTP server
Adafruit_GFX.h             // Graphics library
Adafruit_SSD1306.h         // OLED display driver
NewPing.h                   // Ultrasonic sensor library
```

### Development Tools

- **Python**: 3.8 or higher
- **Arduino IDE**: 1.8.x or 2.x
- **ESP32 Board Package**: Latest version
- **Git**: For version control

---

## 📥 Installation

### 1. Clone the Repository

```bash
git clone https://github.com/DinethraDivanjana2001/Vision-Based-Robot-Arm.git
cd Vision-Based-Robot-Arm
```

### 2. Python Environment Setup

```bash
# Create virtual environment (recommended)
python -m venv venv

# Activate virtual environment
# Windows:
venv\Scripts\activate
# Linux/Mac:
source venv/bin/activate

# Install dependencies
pip install opencv-python mediapipe paho-mqtt cvzone pyfirmata numpy
```

### 3. Arduino/ESP32 Setup

1. **Install Arduino IDE** from [arduino.cc](https://www.arduino.cc/en/software)

2. **Add ESP32 Board Support**:
   - Open Arduino IDE → File → Preferences
   - Add to "Additional Board Manager URLs":
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Tools → Board → Boards Manager → Search "ESP32" → Install

3. **Install Required Libraries**:
   - Sketch → Include Library → Manage Libraries
   - Search and install:
     - ESP32Servo
     - Adafruit GFX Library
     - Adafruit SSD1306
     - NewPing

### 4. Hardware Assembly

1. Connect servos to ESP32 according to pin configuration
2. Wire ultrasonic sensor to GPIO 33
3. Connect OLED display via I2C (SDA→21, SCL→22)
4. Ensure proper power supply for servos (external 5V recommended)
5. Connect ESP32 to computer via USB

### 5. Configuration

#### Python Scripts

Edit connection parameters in `vision/face_to_mqtt_full.py`:

```python
BROKER_HOST  = "your-mqtt-broker.com"
BROKER_PORT  = 1883
ACCESS_TOKEN = "your-access-token"
```

Edit COM port in `vision/facetracking.py`:

```python
port = "COM7"  # Change to your Arduino/ESP32 port
```

#### Arduino Sketches

Update WiFi credentials in `With Interpolation/withinterpolation.ino`:

```cpp
const char* ssid     = "Your-WiFi-SSID";
const char* password = "Your-WiFi-Password";
```

---

## 🚀 Usage Guide

### Mode 1: Face Detection (Standalone)

Simple face detection with visual feedback.

```bash
cd vision
python facedetection.py
```

**Features**:
- Detects multiple faces using Haar Cascade
- Displays bounding boxes
- Shows face count on screen
- Press 'Q' to quit

### Mode 2: Face Tracking with Servo Control

Real-time face tracking with 2-axis servo control.

```bash
cd vision
python facetracking.py
```

**Features**:
- Tracks face center coordinates
- Controls pan-tilt servos via Arduino/ESP32
- Visual crosshair and target lock indicator
- Displays servo angles in real-time

**Requirements**:
- Arduino/ESP32 connected via USB
- Firmata firmware or compatible sketch uploaded
- Correct COM port configured

### Mode 3: Face Detection with MQTT Publishing

Cloud-connected face tracking with telemetry.

```bash
cd vision
python face_to_mqtt_full.py --cam 0
```

**Features**:
- Publishes face coordinates (x, y, z) to MQTT broker
- Real-time cloud monitoring
- Bounding box visualization
- Coordinate display overlay

**MQTT Data Format**:
```json
{
  "x": 0.523,
  "y": 0.412,
  "z": 0.089
}
```

### Mode 4: Autonomous Pick-and-Place

Automated object manipulation using ultrasonic sensing.

**Upload to ESP32**:
1. Open `Moratuwa_expo/Moratuwa_expo.ino` in Arduino IDE
2. Select board: ESP32 Dev Module
3. Select correct COM port
4. Upload sketch

**Operation**:
- Robot initializes to home position
- Waits for object detection (distance < 15cm)
- Executes pick-up sequence
- Moves to drop-off location
- Releases object and returns to home
- Repeats cycle

### Mode 5: Web-Controlled Robot Arm

WiFi-enabled servo control via HTTP API.

**Upload to ESP32**:
1. Open `With Interpolation/withinterpolation.ino`
2. Configure WiFi credentials
3. Upload sketch
4. Note IP address from Serial Monitor

**API Usage**:
```bash
# Set servo positions (microseconds)
curl "http://<ESP32-IP>/set_positions?pos=1500,1600,1400,1500"
```

**Features**:
- Smooth interpolation between positions
- Web-based control interface
- Configurable motion duration
- Multi-servo coordination

---

## 📁 Project Structure

```
Vision-Based-Robot-Arm/
│
├── vision/                              # Computer vision modules
│   ├── facedetection.py                # Basic face detection
│   ├── facetracking.py                 # Face tracking with servo control
│   ├── face_to_mqtt_full.py           # MQTT-enabled face tracking
│   └── haarcascade_frontalface_default.xml  # Haar Cascade model
│
├── Moratuwa_expo/                      # Autonomous pick-and-place
│   └── Moratuwa_expo.ino              # ESP32 sketch with ultrasonic
│
├── With Interpolation/                 # Web-controlled system
│   └── withinterpolation.ino          # WiFi + smooth motion control
│
├── figs/                               # Documentation images
│
├── LICENSE                             # MIT License
└── README.md                           # This file
```

---

## 🔬 Implementation Details

### Computer Vision Pipeline

#### 1. Face Detection (Haar Cascade)

```python
# Load pre-trained classifier
classifier = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")

# Detect faces in grayscale image
faces = classifier.detectMultiScale(
    gray_image,
    scaleFactor=1.3,    # Image pyramid scale
    minNeighbors=2      # Detection threshold
)
```

**Advantages**: Fast, lightweight, CPU-friendly  
**Use Case**: Resource-constrained systems, multiple face detection

#### 2. Face Detection (MediaPipe)

```python
# Initialize MediaPipe face detection
mp_face = mp.solutions.face_detection.FaceDetection(
    model_selection=0,              # 0: short-range, 1: full-range
    min_detection_confidence=0.6    # Confidence threshold
)

# Process frame
results = mp_face.process(rgb_frame)
detections = results.detections
```

**Advantages**: Higher accuracy, ML-based, normalized coordinates  
**Use Case**: Precision tracking, single face scenarios

### Coordinate Mapping

Converting camera coordinates to servo angles:

```python
# Camera resolution
FRAME_W, FRAME_H = 1280, 720

# Extract face center (normalized 0-1)
center_x = bbox.xmin + bbox.width * 0.5
center_y = bbox.ymin + bbox.height * 0.5

# Map to servo range (0-180 degrees)
servo_x = np.interp(center_x * FRAME_W, [0, FRAME_W], [0, 180])
servo_y = np.interp(center_y * FRAME_H, [0, FRAME_H], [0, 180])
```

### Motion Interpolation Algorithm

Smooth servo movement using linear interpolation:

```cpp
void smoothMove(int start[], int end[], int duration) {
    int steps = duration / updateInterval;
    
    // Calculate increments for each servo
    float increments[5];
    for (int i = 0; i < 5; i++) {
        increments[i] = (float)(end[i] - start[i]) / steps;
    }
    
    // Execute interpolated motion
    for (int step = 0; step <= steps; step++) {
        for (int i = 0; i < 5; i++) {
            int position = start[i] + (int)(increments[i] * step);
            servo[i].write(position);
        }
        delay(updateInterval);
    }
}
```

**Benefits**:
- Eliminates jerky movements
- Reduces mechanical stress
- Synchronized multi-servo motion
- Configurable speed control

---

## 📡 Communication Protocols

### MQTT Protocol

**Topic Structure**:
```
v1/devices/me/telemetry    # Telemetry data publishing
v1/devices/me/attributes   # Device attributes
v1/devices/me/rpc/request  # RPC commands (future)
```

**Message Format**:
```json
{
  "x": 0.523,      // Normalized X coordinate (0-1)
  "y": 0.412,      // Normalized Y coordinate (0-1)
  "z": 0.089       // Bounding box area (depth proxy)
}
```

**QoS Levels**:
- QoS 0: Fire and forget (current implementation)
- QoS 1: At least once delivery (recommended for critical data)

### HTTP API (Web Server)

**Endpoint**: `/set_positions`

**Parameters**:
- `pos`: Comma-separated servo positions in microseconds (500-2500)

**Example**:
```
GET /set_positions?pos=1500,1600,1400,1500
```

**Response**:
```
200 OK: "Positions updated"
400 Bad Request: "Invalid position data"
```

### Serial Communication (Firmata)

Used for Arduino-based servo control:

```python
import pyfirmata

board = pyfirmata.Arduino('COM7')
servo_x = board.get_pin('d:9:s')   # Digital pin 9, servo mode
servo_y = board.get_pin('d:10:s')  # Digital pin 10, servo mode

servo_x.write(90)  # Set angle
```

---

## 🎮 Control Algorithms

### PID Control (Future Enhancement)

For smoother tracking and reduced oscillation:

```python
class PIDController:
    def __init__(self, kp, ki, kd):
        self.kp = kp  # Proportional gain
        self.ki = ki  # Integral gain
        self.kd = kd  # Derivative gain
        self.prev_error = 0
        self.integral = 0
    
    def compute(self, setpoint, measured):
        error = setpoint - measured
        self.integral += error
        derivative = error - self.prev_error
        
        output = (self.kp * error + 
                 self.ki * self.integral + 
                 self.kd * derivative)
        
        self.prev_error = error
        return output
```

### Inverse Kinematics (Future Enhancement)

For precise end-effector positioning:

```python
def inverse_kinematics(x, y, z, L1, L2, L3):
    """
    Calculate joint angles for desired position
    x, y, z: Target coordinates
    L1, L2, L3: Link lengths
    Returns: [theta1, theta2, theta3, theta4, theta5]
    """
    # Base rotation
    theta1 = atan2(y, x)
    
    # Arm reach calculation
    r = sqrt(x**2 + y**2)
    # ... (full IK implementation)
    
    return joint_angles
```

---

## 🎯 Applications

### Educational

- **STEM Learning**: Demonstrates robotics, computer vision, and control systems
- **University Projects**: Mechatronics, AI, embedded systems coursework
- **Workshops**: Hands-on training for robotics enthusiasts

### Industrial Prototyping

- **Quality Inspection**: Vision-based defect detection
- **Assembly Line**: Pick-and-place automation
- **Sorting Systems**: Object classification and handling

### Research & Development

- **Human-Robot Interaction**: Gesture recognition and response
- **Autonomous Systems**: Vision-guided navigation
- **IoT Integration**: Cloud-connected robotics platforms

### Entertainment

- **Interactive Installations**: Art exhibits with audience interaction
- **Gaming**: Physical game controllers and interfaces
- **Social Robots**: Face tracking for engagement

---

## 🚀 Future Enhancements

### Short-Term Goals

- [ ] **Object Recognition**: Extend beyond faces to detect and classify objects
- [ ] **Color Tracking**: Track objects based on color segmentation
- [ ] **Gesture Control**: Hand gesture recognition for intuitive control
- [ ] **Mobile App**: Android/iOS app for remote operation
- [ ] **Voice Commands**: Speech recognition for hands-free control

### Medium-Term Goals

- [ ] **Machine Learning**: Train custom models for specific objects
- [ ] **Path Planning**: Obstacle avoidance and trajectory optimization
- [ ] **Multi-Robot Coordination**: Synchronize multiple robot arms
- [ ] **Force Feedback**: Pressure sensors for delicate object handling
- [ ] **3D Vision**: Stereo cameras for depth perception

### Long-Term Vision

- [ ] **Autonomous Learning**: Reinforcement learning for task optimization
- [ ] **Digital Twin**: Real-time simulation and virtual testing
- [ ] **AR Integration**: Augmented reality visualization and control
- [ ] **Edge AI**: On-device ML inference with TensorFlow Lite
- [ ] **ROS Integration**: Robot Operating System compatibility

---

## 🛠️ Troubleshooting

### Camera Issues

**Problem**: Camera not detected  
**Solutions**:
- Check USB connection and try different ports
- Verify camera index (try `--cam 1` or `--cam 2`)
- Test camera with: `python -c "import cv2; print(cv2.VideoCapture(0).isOpened())"`
- Update camera drivers

**Problem**: Low frame rate  
**Solutions**:
- Reduce resolution: `cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)`
- Use Haar Cascade instead of MediaPipe
- Close other applications using camera

### Servo Control Issues

**Problem**: Servos not responding  
**Solutions**:
- Check power supply (servos need 5V 2-3A)
- Verify pin connections match code configuration
- Test individual servos with simple sketch
- Ensure common ground between ESP32 and servo power

**Problem**: Jittery servo movement  
**Solutions**:
- Add capacitors (100µF) across servo power lines
- Increase interpolation steps for smoother motion
- Use external power supply (not USB)
- Check for loose connections

### MQTT Connection Issues

**Problem**: Cannot connect to broker  
**Solutions**:
- Verify broker URL and port (usually 1883)
- Check access token/credentials
- Test with MQTT client (MQTT Explorer, mosquitto_pub)
- Ensure firewall allows MQTT traffic
- Try public broker for testing: `test.mosquitto.org`

### ESP32 Upload Issues

**Problem**: Upload fails  
**Solutions**:
- Hold BOOT button during upload
- Select correct board: "ESP32 Dev Module"
- Reduce upload speed: Tools → Upload Speed → 115200
- Check COM port selection
- Install CP210x or CH340 drivers

### Face Detection Issues

**Problem**: Faces not detected  
**Solutions**:
- Ensure good lighting conditions
- Reduce `min_detection_confidence` value
- Try different camera angles
- Verify Haar Cascade XML file path
- Check if face is within camera frame

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

### Reporting Bugs

1. Check existing issues to avoid duplicates
2. Provide detailed description with steps to reproduce
3. Include error messages and screenshots
4. Specify hardware/software versions

### Suggesting Features

1. Open an issue with `[Feature Request]` tag
2. Describe use case and expected behavior
3. Provide mockups or examples if applicable

### Code Contributions

1. Fork the repository
2. Create feature branch: `git checkout -b feature/amazing-feature`
3. Commit changes: `git commit -m 'Add amazing feature'`
4. Push to branch: `git push origin feature/amazing-feature`
5. Open Pull Request with detailed description

### Code Style Guidelines

- **Python**: Follow PEP 8 style guide
- **C++/Arduino**: Use consistent indentation (2 spaces)
- **Comments**: Document complex logic and algorithms
- **Naming**: Use descriptive variable and function names

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2024 Dinethra Divanjana

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software...
```

---

## 🙏 Acknowledgments

### Libraries & Frameworks

- **OpenCV**: Open source computer vision library
- **MediaPipe**: Google's ML solutions for live perception
- **Arduino/ESP32**: Open-source electronics platform
- **Paho MQTT**: Eclipse IoT messaging library

### Inspiration & Resources

- **Moratuwa University Expo**: Project demonstration platform
- **Robotics Community**: Forums and tutorials
- **Open Source Contributors**: Countless developers worldwide

### Special Thanks

- Computer vision researchers for advancing the field
- Arduino and ESP32 communities for excellent documentation
- All contributors and users of this project

---

## 📞 Contact & Support

- **GitHub Issues**: [Report bugs or request features](https://github.com/DinethraDivanjana2001/Vision-Based-Robot-Arm/issues)
- **Discussions**: [Ask questions and share ideas](https://github.com/DinethraDivanjana2001/Vision-Based-Robot-Arm/discussions)
- **Email**: [Contact maintainer](mailto:your-email@example.com)

---

## 🌟 Star History

If you find this project useful, please consider giving it a ⭐ on GitHub!

---

## 📊 Project Statistics

- **Lines of Code**: ~500+ (Python + Arduino)
- **Supported Platforms**: Windows, Linux, macOS
- **Hardware Compatibility**: ESP32, Arduino Uno/Mega
- **Vision Models**: Haar Cascade, MediaPipe
- **Communication Protocols**: MQTT, HTTP, Serial

---

<div align="center">

**Made with ❤️ for robotics enthusiasts**

[⬆ Back to Top](#-vision-based-robot-arm)

</div>
