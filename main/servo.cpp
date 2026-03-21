Servo myServo;
#define SERVO_PIN 15

void init_servo(){
    // Servo setup
  myServo.setPeriodHertz(50);      // Standard 50Hz servo
  myServo.attach(SERVO_PIN, 500, 2400); // Min & max pulse width
}

void drive_servo_up(){
  
}