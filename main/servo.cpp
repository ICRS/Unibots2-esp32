#include <ESP32Servo.h>
Servo myServo;
#define SERVO_PIN 15

void init_servo(){
    // Servo setup
  myServo.setPeriodHertz(50);      // Standard 50Hz servo
  myServo.attach(SERVO_PIN, 500, 2400); // Min & max pulse width
}

void drive_servo_up(){
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(10);
  }
}

void drive_servo_down(){
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(10);
  }
}