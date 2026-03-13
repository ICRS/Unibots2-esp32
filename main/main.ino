// DRV8833 test pins
constexpr int UNDEFINED_PIN = 2;

constexpr unsigned long BAUD_RATE = 115200;


constexpr unsigned int LEFT_MOTOR_DRIVER_IN1 = 25;
constexpr unsigned int LEFT_MOTOR_DRIVER_IN2 = 26;
constexpr unsigned int LEFT_MOTOR_DRIVER_IN3 = 12;
constexpr unsigned int LEFT_MOTOR_DRIVER_IN4 = 13;
constexpr unsigned int LEFT_MOTOR_DRIVER_SLEEP = 14;
constexpr unsigned int LEFT_MOTOR_DRIVER_FAULT = 27;


constexpr unsigned int RIGHT_MOTOR_DRIVER_IN1 = 19;
constexpr unsigned int RIGHT_MOTOR_DRIVER_IN2 = 18;
constexpr unsigned int RIGHT_MOTOR_DRIVER_IN3 = 4;
constexpr unsigned int RIGHT_MOTOR_DRIVER_IN4 = 16;
constexpr unsigned int RIGHT_MOTOR_DRIVER_SLEEP = 17;
constexpr unsigned int RIGHT_MOTOR_DRIVER_FAULT = 5;


void setup() {
  pinMode(LEFT_MOTOR_DRIVER_IN1,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_IN2,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_IN3,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_IN4,    OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_SLEEP,  OUTPUT);
  pinMode(LEFT_MOTOR_DRIVER_FAULT,  INPUT_PULLUP);

  pinMode(RIGHT_MOTOR_DRIVER_IN1,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_IN2,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_IN3,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_IN4,   OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_SLEEP, OUTPUT);
  pinMode(RIGHT_MOTOR_DRIVER_FAULT,  INPUT_PULLUP);

  // Ensure motors start off
  digitalWrite(LEFT_MOTOR_DRIVER_IN1,     LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN2,     LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN3,     LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN4,     LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_SLEEP,   HIGH);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN1,    LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN2,    LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN3,    LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN4,    LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_SLEEP,  HIGH);
  Serial.begin(BAUD_RATE);
}

void loop() {
  int fault;
  // Test Motor A
  digitalWrite(LEFT_MOTOR_DRIVER_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_DRIVER_IN2, LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN3, HIGH);
  digitalWrite(LEFT_MOTOR_DRIVER_IN4, LOW);
  fault = digitalRead(LEFT_MOTOR_DRIVER_FAULT);
  Serial.print("left driver fault 1: ");
  Serial.println(fault);
  delay(1000);

  digitalWrite(LEFT_MOTOR_DRIVER_IN1, LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN2, LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN3, LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN4, LOW);
  fault = digitalRead(LEFT_MOTOR_DRIVER_FAULT);
  Serial.print("left driver fault 2: ");
  Serial.println(fault);
  delay(1000);

  digitalWrite(LEFT_MOTOR_DRIVER_IN1, LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN2, HIGH);
  digitalWrite(LEFT_MOTOR_DRIVER_IN3, LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN4, HIGH);
  fault = digitalRead(LEFT_MOTOR_DRIVER_FAULT);
  Serial.print("left driver fault: 3: ");
  Serial.println(fault);
  delay(1000);

  digitalWrite(LEFT_MOTOR_DRIVER_IN1, LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN2, LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN3, LOW);
  digitalWrite(LEFT_MOTOR_DRIVER_IN4, LOW);
  fault = digitalRead(LEFT_MOTOR_DRIVER_FAULT);
  Serial.print("left driver fault 4: ");
  Serial.println(fault);
  delay(1000);
  
  // Test Motor B
  digitalWrite(RIGHT_MOTOR_DRIVER_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN3, HIGH);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN4, LOW);
  fault = digitalRead(RIGHT_MOTOR_DRIVER_FAULT);
  Serial.print("right motor driver fault 1: ");
  Serial.println(fault);
  delay(1000);

  digitalWrite(RIGHT_MOTOR_DRIVER_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN4, LOW);
  fault = digitalRead(RIGHT_MOTOR_DRIVER_FAULT);
  Serial.print("right motor driver fault 2: ");
  Serial.println(fault);
  delay(1000);

  digitalWrite(RIGHT_MOTOR_DRIVER_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN2, HIGH);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN4, HIGH);
  fault = digitalRead(RIGHT_MOTOR_DRIVER_FAULT);
  Serial.print("right motor driver fault  3: ");
  Serial.println(fault);
  delay(1000);

  digitalWrite(RIGHT_MOTOR_DRIVER_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_DRIVER_IN4, LOW);
  fault = digitalRead(RIGHT_MOTOR_DRIVER_FAULT);
  Serial.print("right motor driver fault 4: ");
  Serial.println(fault);
  delay(1000);

}