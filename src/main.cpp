#include <Arduino.h>
#include <WString.h>
#include <view/LCDview.h>
#include <LiquidCrystal_I2C.h>
#include <model/WiFiHandler.h>
#include <model/WebSetup.h>
#include "model/PumpControl.h"

// -------------- Websetup --------------
const char* ssid = "Pixel_3583";
const char* password = "wlanding";

const int webport = 80;
// -------------- End Websetup --------------
// -------------- PumpControl --------------
const float tempdivForActivePump = 8;
const float tempdivForDeactivePump = 4;
const float minTimeActivePump = 2;    // in minutes 
const float maxTempStorage = 80;  // in °C
// -------------- End PumpControl --------------

const int MEASURE_PIN0 = A0;
const int MEASURE_PIN1 = A1;
const int PUMP_PIN = D2;    

const int lcdAdresseI2C = 0x27;
const int lcdSpalten = 20;
const int lcdZeilen = 4;

// TODO: wird noch benötigt?
// unbekannt ob nächste Zeile benötigt wird
// const int amplification = 100;
const float vt_factor = 1.88;
const float offset = 0;



void setup() {
  // sets the resolution of the analogRead
  analogReadResolution(12);
  // sets the baud rate for serial data transmission
  Serial.begin(9600);
  // init LCD
  LCDview lcd(lcdAdresseI2C, lcdSpalten, lcdZeilen);
  WiFiHandler wifi(ssid, password);
  WebSetup webSetup(webport);
  PumpControl control(tempdivForActivePump, 
    tempdivForDeactivePump, minTimeActivePump, 
    maxTempStorage, MEASURE_PIN0, MEASURE_PIN1, 
    PUMP_PIN
  );
  String pumpText = "off";

  while(true) {
    try {
      wifi.connect();
      webSetup.start();
      lcd.printIP(wifi.getIPadress());
    } catch (WiFiHandler::ConnectionTimeoutException e) {
      Serial.println(e.what());
      lcd.printIP("disconnected");
    }
    
    // TODO: Abfrage durch event? (timing)
    do {
      control.controlPump();
      if(control.isPumpActive()){
        pumpText = "on";
      } else {
        pumpText = "off";
      }

      lcd.setTemp1(String(control.getTemp1(), 1));
      lcd.setTemp2(String(control.getTemp2(), 1));
      lcd.setPumpMode(pumpText);
      
      webSetup.handleClient(String(control.getTemp1(), 1), String(control.getTemp2(), 1), pumpText);
      
      
      delay(500);
    }while(wifi.isConnected());
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