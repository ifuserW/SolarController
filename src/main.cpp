#include <Arduino.h>
#include <WString.h>
#include <view/LCDview.h>
#include <LiquidCrystal_I2C.h>
#include <model/WebSetup.h>

// -------------- Websetup --------------
const char* ssid = "FRITZ!Box 6850 BN";
const char* password = "37291315686167945817";
const int webport = 80;
// -------------- End Websetup --------------
// -------------- PumpControl --------------
int tempdivForActivePump = 8;
int tempdivForDeactivePump = 4;
int minTimeActivePump = 3;    // in minutes
int maxTempCollector = 80; 
// -------------- End PumpControl --------------

const int MEASURE_PIN0 = A0;
const int MEASURE_PIN1 = A1;
// LCDview(AdresseI2C, Spalten, Zeilen)
const int lcdAdresseI2C = 0x27;
const int lcdSpalten = 20;
const int lcdZeilen = 4;
// unbekannt ob nächste Zeile benötigt wird
// const int amplification = 100;
const float vt_factor = 1.88;
const float offset = 0;

float voltagePin0 = 0;
float voltagePin1 = 0;
int readValuePin0 = 0;
int readValuePin1 = 0;
float tempCollector;
float tempStorage;


void setup() {
  // sets the resolution of the analogRead
  analogReadResolution(12);
  // sets the baud rate for serial data transmission
  Serial.begin(9600);
  // init LCD
  LCDview lcd(lcdAdresseI2C, lcdSpalten, lcdZeilen);
  WebSetup webSetup(ssid, password, webport);
  while(true) {
    webSetup.connect();
    lcd.printIP(webSetup.getIPadress());
    // TODO: Abfrage, ob verbindung noch da in regelmäßigen Abständen
    while(true){
      readValuePin0 = analogRead(MEASURE_PIN0);
      readValuePin1 = analogRead(MEASURE_PIN1);
      voltagePin0 = readValuePin0 * (3.3 / 4095.0);
      voltagePin1 = readValuePin1 * (3.3 / 4095.0);

      // klären wofür *100 stehen
      tempCollector = ((voltagePin0 * 212.904) + 820);
      tempStorage = ((voltagePin1 * 212.904) + 820);


      lcd.setTemp1(String(voltagePin0, 2));
      lcd.setTemp2(String(voltagePin1, 2));
      lcd.setPumpMode("TODO");
      Serial.print(voltagePin0);
      Serial.print(voltagePin1);
      Serial.print(" V Temp: ");
      Serial.println(tempCollector, 1);
      Serial.println(tempStorage, 1);
      webSetup.handleClient(String(voltagePin0, 2), String(voltagePin0, 2), "TODO");
      delay(500);
    }
  }
}

void loop() {
//   readValuePin0 = analogRead(MEASURE_PIN);
//   voltagePin0 = readValuePin0 * (3.3 / 4095.0);
//   // klären wofür *100 stehen
//   temp_c = (((voltagePin0 * 100) / vt_factor) + offset);
//   Serial.print(voltagePin0);
//   lcd.setTemp1("Temp1: " + String(temp_c, 1));
//   Serial.print(" V Temp: ");
//   Serial.println(temp_c, 1);
//   delay(500);
}