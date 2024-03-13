#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address and dimensions (16x2)

const int piezoPin = A0;  // Analog pin connected to the piezoelectric generator
const int threshold = 10; // Adjust this threshold according to your piezo sensor's sensitivity

int footstepCount = 0;
float voltage = 0.0;

void setup() {
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.setCursor(0, 1);
  lcd.print("Footsteps: ");
}

void loop() {
  // Read voltage from piezoelectric generator
  int sensorValue = analogRead(piezoPin);
  voltage = sensorValue * (5.0 / 1023.0); // Convert analog reading to voltage

  // Count footsteps if voltage exceeds threshold
  if (sensorValue > threshold) {
    footstepCount++;
    delay(200); // Debounce delay to prevent multiple counts for a single step
  }

  // Update LCD
  lcd.setCursor(9, 0);
  lcd.print(voltage);
  lcd.setCursor(11, 1);
  lcd.print(footstepCount);

  delay(500); // Adjust delay according to your preference and system requirements
}
