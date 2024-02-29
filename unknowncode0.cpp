const int lm35Pin = A0;    // LM35 temperature sensor analog pin
const int motorPin1 = 2;   // L298N motor driver input pin 1
const int motorPin2 = 3;   // L298N motor driver input pin 2
const int stepsToStop = 200;  // Adjust this value based on your setup and required distance

int stepsCounter = 0;

void setup() {
  pinMode(lm35Pin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
  // Read temperature from LM35 sensor
  int temperature = analogRead(lm35Pin);
  float celsius = (temperature / 1024.0) * 500.0;  // Convert analog reading to Celsius

  // Check temperature conditions
  if (celsius >= 33) {
    // Rotate clockwise
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    stepsCounter++;
  } else if (celsius <= 30) {
    // Rotate counterclockwise
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    stepsCounter++;
  } else {
    // Stop the motor
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    stepsCounter = 0;  // Reset the counter when not rotating
  }

  // Check if the predefined number of steps is reached
  if (stepsCounter >= stepsToStop) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    stepsCounter = 0;  // Reset the counter to prepare for the next rotation
  }

  // Add a delay or other control mechanisms as needed
  delay(100);  // Adjust the delay based on your project requirements
}
