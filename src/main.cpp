#include <Arduino.h>
#include <WString.h>
#include <view/LCDview.h>
// #include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <model/WebSetup.h>

WebSetup webView;
const int MEASURE_PIN = A0;
int lcdAdresseI2C = 0x27;
int lcdSpalten = 20;
int lcdZeilen = 4;
LCDview lcd(lcdAdresseI2C, lcdSpalten, lcdZeilen);
// unbekannt ob nächste Zeile benötigt wird
// const int amplification = 100;
const float vt_factor = 1.88;
const float offset = 0;
float voltage = 0;
int readValue = 0;
float temp_c;


void setup() {
  // init LCD
  // sets the resolution of the analogRead
  analogReadResolution(12);
  // sets the baud rate for serial data transmission
  // LCDview lcd(lcdAdresseI2C, lcdSpalten, lcdZeilen);

  readValue = analogRead(MEASURE_PIN);
  voltage = readValue * (3.3 / 4095.0);
  // klären wofür *100 stehen
  temp_c = ((voltage * 212.904) + 820);
  lcd.setTemp1(String(voltage, 1));
  lcd.setTemp2(String(voltage, 1));
  lcd.setPumpMode("TODO");

  Serial.print(voltage);
  Serial.print(" V Temp: ");
  Serial.println(temp_c, 1);
  while(true) {
    readValue = analogRead(MEASURE_PIN);
    voltage = readValue * (3.3 / 4095.0);
    // klären wofür *100 stehen
    temp_c = ((voltage * 212.904) + 820);
    lcd.setTemp1(String(voltage, 1));
    lcd.setTemp2(String(voltage, 1));
    lcd.setPumpMode("TODO");

    Serial.print(voltage);
    Serial.print(" V Temp: ");
    Serial.println(temp_c, 1);
    delay(500);
    webView.handleClient();
  }
}


void loop() {
  
}