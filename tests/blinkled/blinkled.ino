//ESP32 Onboard LED Blink code from www.theorycircuit.com
// Define the LED pin
const int ledPin = 2; // Built-in LED pin on most ESP32 boards

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(ledPin, HIGH);
  // Wait for a second
  delay(1000);
  // Turn the LED off
  digitalWrite(ledPin, LOW);
  // Wait for a second
  delay(1000);
}