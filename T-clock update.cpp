#include <Wire.h> // Inilagay ang Wire library para sa I2C communication
#include <LiquidCrystal_I2C.h> // Inilagay ang LiquidCrystal_I2C library para sa LCD display
#include <DS1302.h> // Inilagay ang DS1302 library para sa RTC module

LiquidCrystal_I2C lcd(0x3F, 16, 2); // Nilikha ang isang instance ng LiquidCrystal_I2C class para sa LCD, na konektado sa address na 0x3F, at may 16 characters at 2 rows
DS1302 rtc(2, 3, 4); // Nilikha ang isang instance ng DS1302 class para sa RTC, na konektado sa pins 2 (CLK), 3 (DAT), at 4 (RST)

int pset = 8; // Pin para sa pag-set ng alarm
int phour = 9; // Pin para sa oras
int pmin = 10; // Pin para sa minuto
int pexit = 11; // Pin para sa pag-exit
int buzzer = 6; // Pin para sa buzzer
int Hour;
int Min;
int h = 0; // Initial value ng oras sa alarm
int m = 0; // Initial value ng minuto sa alarm
int activate = 0; // Flag para sa pag-activate o pag-deactivate ng pag-set ng alarm
bool alarmActive = false; // Flag para sa pag-activate o pag-deactivate ng alarm

void setup() {
  pinMode(pset, INPUT);
  pinMode(phour, INPUT);
  pinMode(pmin, INPUT);
  pinMode(pexit, INPUT);
  pinMode(buzzer, OUTPUT); // Itinakda ang mga pin bilang input o output
  
  lcd.begin(16, 2); // Inisyalisasyon ng LCD
  rtc.halt(false); // Binuksan ang RTC
  rtc.writeProtect(false); // Tinanggal ang write protection ng RTC

  // Kung nais mong itakda ang oras at petsa sa simula, i-uncomment ang mga sumusunod:
  // rtc.setTime(12, 0, 0); // Itakda ang oras sa 12:00:00
  // rtc.setDate(11, 11, 2024); // Itakda ang petsa sa November 11, 2024
}

void loop() {
  if (!alarmActive) {
    displayTime(); // Ipakita ang oras at petsa sa LCD
    checkAlarmButton(); // Subukin kung pinindot ang button para sa pag-set ng alarm
  } else {
    setAlarm(); // Kung naka-activate ang pag-set ng alarm, i-set ito
  }

  checkAlarm(); // Subukin kung tama na ang oras para sa alarm
  delay(500); // Delay para sa pag-iwas sa mabilisang pag-check ng oras
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
    activate = !activate; // Toggle ng flag para sa pag-set ng alarm
    lcd.clear(); // Linisin ang LCD display
    delay(300); // Delay para sa debounce
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
    h = (h + 1) % 24; // Bawat pagpindot sa button ay magdadagdag ng oras
    lcd.setCursor(5, 1);
    lcd.print(h);
    delay(200); // Delay para sa debounce
  }

  if (digitalRead(pmin) == HIGH) {
    m = (m + 1) % 60; // Bawat pagpindot sa button ay magdadagdag ng minuto
    lcd.setCursor(13, 1);
    lcd.print(m);
    delay(200); // Delay para sa debounce
  }

  if (digitalRead(pexit) == HIGH) {
    activate = 0; // I-deactivate ang pag-set ng alarm
    lcd.clear(); // Linisin ang LCD display
    delay(300); // Delay para sa debounce
    alarmActive = false; // I-deactivate ang alarm
  }
}

void checkAlarm() {
  if (activate && !alarmActive) {
    DateTime now = rtc.now(); // Kunin ang kasalukuyang oras mula sa RTC
    Hour = now.hour; // Kunin ang oras
    Min = now.minute; // Kunin ang minuto

    if (Hour == h && Min == m) { // Kung ang kasalukuyang oras ay tumugma sa oras ng alarm
      tone(buzzer, 400, 300); // Bumusina ang buzzer
      alarmActive = true; // I-activate ang alarm
    }
  }
}
