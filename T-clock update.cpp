#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
DS1302 rtc(2, 3, 4);

int pset = 8; // pushbutton for setting alarm
int phour = 9; // pushbutton for hour
int pmin = 10; // pushbutton for minutes
int pexit = 11; // pushbutton for exit 
int buzzer = 6; 
int Hour;
int Min;
int h = 0;
int m = 0;
int activate = 0;
bool alarmActive = false;

void setup() {
  pinMode(pset, INPUT);
  pinMode(phour, INPUT);
  pinMode(pmin, INPUT);
  pinMode(pexit, INPUT);
  pinMode(buzzer, OUTPUT);
  
  lcd.begin();
  rtc.halt(false);
  rtc.writeProtect(false);

  // Uncomment below if you want to set initial time and date
  // rtc.setTime(12, 0, 0); // Set the time to 12:00:00
  // rtc.setDate(11, 11, 2024); // Set the date to November 11th, 2024
}

void loop() {
  if (!alarmActive) {
    displayTime();
    checkAlarmButton();
  } else {
    setAlarm();
  }

  checkAlarm();
  delay(500);
}

void displayTime() {
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(6, 0);
  lcd.print(rtc.getTimeStr());

  lcd.setCursor(0, 1);
  lcd.print("Date:");
  lcd.setCursor(6, 1);
  lcd.print(rtc.getDateStr());
}

void checkAlarmButton() {
  if (digitalRead(pset) == HIGH) {
    activate = !activate;
    lcd.clear();
    delay(300); // Debounce delay
  }
}

void setAlarm() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Alarm");
  lcd.setCursor(0, 1);
  lcd.print("Hour=");
  lcd.print(h);
  lcd.setCursor(9, 1);
  lcd.print("Min=");
  lcd.print(m);

  if (digitalRead(phour) == HIGH) {
    h = (h + 1) % 24;
    lcd.setCursor(5, 1);
    lcd.print(h);
    delay(200); // Debounce delay
  }

  if (digitalRead(pmin) == HIGH) {
    m = (m + 1) % 60;
    lcd.setCursor(13, 1);
    lcd.print(m);
    delay(200); // Debounce delay
  }

  if (digitalRead(pexit) == HIGH) {
    activate = 0;
    lcd.clear();
    delay(300); // Debounce delay
    alarmActive = false;
  }
}

void checkAlarm() {
  if (activate && !alarmActive) {
    DateTime now = rtc.now();
    Hour = now.hour;
    Min = now.minute;

    if (Hour == h && Min == m) {
      tone(buzzer, 400, 300);
      alarmActive = true;
    }
  }
}
