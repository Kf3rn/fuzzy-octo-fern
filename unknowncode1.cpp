#include <LiquidCrystal_I2C.h>

const int piezoPin = A0;  // Analog pin for the piezoelectric sensor
const int ledPin = 13;    // LED pin for visual feedback
const int lcdAddr = 0x27; // I2C address of the LCD display
const int lcdCols = 16;   // Number of columns in the LCD display

LiquidCrystal_I2C lcd(lcdAddr, lcdCols, 2);

int footstepCount = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Footsteps: 0");
}

void loop() {
  int sensorValue = analogRead(piezoPin);
  
  if (sensorValue > 50) {  // Adjust this threshold based on your setup
    footstepCount++;
    digitalWrite(ledPin, HIGH);  // Turn on LED for visual feedback
    delay(100);  // Adjust delay as needed
    digitalWrite(ledPin, LOW);   // Turn off LED
    
    float voltage = sensorValue * (5.0 / 1023.0);  // Convert analog reading to voltage
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Footsteps: ");
    lcd.print(footstepCount);
    lcd.setCursor(0, 1);
    lcd.print("Voltage: ");
    lcd.print(voltage, 2);  // Display voltage with 2 decimal places
    lcd.print("V");
  }
}
