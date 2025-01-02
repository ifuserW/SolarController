#include <Arduino.h>
#include <WString.h>
#include <view/LCDview.h>
// #include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int MEASURE_PIN = A0;
// LCDview(AdresseI2C, Spalten, Zeilen)
int lcdAdresseI2C = 0x27;
int lcdSpalten = 20;
int lcdZeilen = 4;
// unbekannt ob nächste Zeile benötigt wird
// const int amplification = 100;
const float vt_factor = 1.88;
const float offset = 0;
float voltage = 0;
int readValue = 0;
float temp_c;

void setup() {
  // init LCD
  LCDview lcd(lcdAdresseI2C, lcdSpalten, lcdZeilen);
  // sets the resolution of the analogRead
  analogReadResolution(12);
  // sets the baud rate for serial data transmission
  Serial.begin(9600);
  while(true){
    readValue = analogRead(MEASURE_PIN);
    voltage = readValue * (3.3 / 4095.0);
    // klären wofür *100 stehen
    temp_c = ((voltage * 212.904) + 820);
    Serial.print(voltage);
    lcd.print("voltage: " + String(voltage) + "O: " + String(temp_c));
    Serial.print(" V Temp: ");
    Serial.println(temp_c, 1);
    delay(500);
  }
}

void loop() {
//   readValue = analogRead(MEASURE_PIN);
//   voltage = readValue * (3.3 / 4095.0);
//   // klären wofür *100 stehen
//   temp_c = (((voltage * 100) / vt_factor) + offset);
//   Serial.print(voltage);
//   lcd.setTemp1("Temp1: " + String(temp_c, 1));
//   Serial.print(" V Temp: ");
//   Serial.println(temp_c, 1);
//   delay(500);
}