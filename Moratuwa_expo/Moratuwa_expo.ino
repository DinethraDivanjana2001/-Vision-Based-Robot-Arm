#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>
  

Adafruit_SSD1306 display(128, 64);


#define servo1 26
#define servo2 4
#define servo3 13
// #define servo3 14
#define servo4 15
#define servo5 2

Servo servo[5];
Servo servo2a;


#define TRIGGER_PIN 33 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 33
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

///increase(right),inrease(up), decrease (up),increase(down), decrease(close)
int initial[] =      {110, 130,140,70,120 };

int MoveTopickup[] = {150, 50, 150, 90,120 };

int pickUp[] =       {150, 10, 150, 50, 120};
int grab[] =         {150, 10, 140, 50, 60};

int HoldingAfterPickUp[] = {160, 50, 150, 90, 60};
int HoldingCenter[] =  {110, 50,140,70, 60 };

int MoveToUnload[] = {15, 50, 180, 30, 60 };
int unload[] =       {10, 10,180, 50, 60};
int drop[] = {15, 10,180, 50, 120};
int NotHoldingCenter[] =  {110, 50,140,70, 120 };



// int pickUp[] = {0, 10, 30, 70, 60 };


int current_pos[] = {0,0,0,0,0};
int target_pos[] = {0,0,0,0,0};

long lastTime = 0;
bool onMove = 0;

int distance;

void setup() {
  servo[0].attach(servo1);
  servo[1].attach(servo2);
  // servo2a.attach(servo2A);
  servo[2].attach(servo3);
  servo[3].attach(servo4);
  servo[4].attach(servo5);

  Serial.begin(115200);

  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.setTextSize(1);


  //initialize servos 
  inialize_servos(initial);
  delay(3000);
  distance = sonar.ping_cm();
  if (distance == 0){
    distance = 1000;
  }
  while (distance > 15){
  distance = sonar.ping_cm();
     if (distance == 0){
    distance = 1000;
  }
  Serial.println(distance);
  }
  delay(5000);
  PickUpBox();
  GotoCenterHolding();

  UnloadBox();
  GotoCenterWithout();

}



void PickUpBox(){
  setTarget(MoveTopickup);
  move_servos();
  delay(1000);
  setTarget(pickUp);
  move_servos();
  delay(1000);
  setTarget(grab);
  move_servos();
  delay(100);
  setTarget(HoldingAfterPickUp);
  move_servos();
  delay(100);
}


void GotoCenterHolding(){
  setTarget(HoldingCenter);
  move_servos();
  delay(100);
}
void GotoCenterWithout(){
  setTarget(NotHoldingCenter);
  move_servos();
  delay(100);
}

void UnloadBox(){
  setTarget(MoveToUnload);
  move_servos();
  delay(100);
  setTarget(unload);
  move_servos();
  delay(100);
  setTarget(drop);
  move_servos();
  delay(100);
  setTarget(MoveToUnload);
  move_servos();
  delay(100);
}



// void liftBox(){  
//   setTarget(pickUp);
//   move_servos();
//   grab();

//   // delay(500);
//   // setTarget(HoldingAfterPickUp);
//   // move_servos();

// }

void inialize_servos(int angles[]) {
  for(int j=4;j>-1;j--){
      servo[j].write(angles[j]);
      current_pos[j] = angles[j];
      delay(10);
    }
}


void setTarget(int a[5]) {
  target_pos[0] = a[0];
  target_pos[1] = a[1];
  target_pos[2] = a[2];
  target_pos[3] = a[3];
  target_pos[4] = a[4];
}

void move_servos() {
  int movement_state[5];
  while (1) {
    if ((millis() - lastTime) > 15) {
      onMove = 0;
      for (int i = 0; i < 5; i++) {
        if ((current_pos[i] - target_pos[i]) > 0) {
          current_pos[i]--;
          servo[i].write(current_pos[i]);
          // servos.setPWM(i, 0, angleToPulse(current_pos[i]));
          movement_state[i] = 1;
        }
        if ((current_pos[i] - target_pos[i]) < 0) {
          current_pos[i]++;
         servo[i].write(current_pos[i]);
          // servos.setPWM(i, 0, angleToPulse(current_pos[i]));
          movement_state[i] = 1;
        }
        if (current_pos[i] == target_pos[i]) {
          movement_state[i] = 0;
        }
      }
      onMove = movement_state[0] | movement_state[1] | movement_state[2] | movement_state[3] | movement_state[4];
      lastTime = millis();
    }
    if (!onMove) {   
      break;
    }
  }
}

void loop() {

distance = sonar.ping_cm();
  if (distance == 0){
    distance = 1000;
  }
  while (distance > 10){
  distance = sonar.ping_cm();
     if (distance == 0){
    distance = 1000;
  }
  // Serial.println(distance);
  }
  delay(5000);
  PickUpBox();
  GotoCenterHolding();

  UnloadBox();
  GotoCenterWithout();


}
