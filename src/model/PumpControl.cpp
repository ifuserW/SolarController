#include "PumpControl.h"

PumpControl::PumpControl(const int tempdivForActivePump, 
    const int tempdivForDeactivePump, 
    const int minTimeActivePump, 
    const int maxTempStorage,
    const int pin0, 
    const int pin1, 
    const int pinPump)
    : tempdivForActivePump(tempdivForActivePump), 
    tempdivForDeactivePump(tempdivForDeactivePump), 
    minTimeActivePump(minTimeActivePump), 
    maxTempStorage(maxTempStorage),
    sensorCollector(pin0),  // Initialize PT1000 sensors here
    sensorStorage(pin1),    // Initialize PT1000 sensors here
    pinPump(pinPump),    // Initialize pump control settings here
    pumpState(false),
    lastTimePumpOn(0)  {

    // Initialize pump control settings here
    pinMode(pinPump, OUTPUT);
    digitalWrite(pinPump, LOW);
}


void PumpControl::controlPump() {
    sensorCollector.readTemp();
    sensorStorage.readTemp();
    

    Serial.println("1: " + String(sensorCollector.getVoltage()) 
    + " V1 Temp: " + String(sensorCollector.getTemp(), 1));
    Serial.println("2: " + String(sensorStorage.getVoltage()) 
    + " V1 Temp: " + String(sensorStorage.getTemp(), 1));
    
    // Pumpensteuerungslogik
    if (sensorStorage.getTemp() > maxTempStorage) {
        turnPumpOff();
    } else if (sensorCollector.getTemp() - sensorStorage.getTemp() >= tempdivForActivePump) {
        if (!pumpState) {
            turnPumpOn();
            lastTimePumpOn = millis();
        }
    } else if (sensorCollector.getTemp() - sensorStorage.getTemp() <= tempdivForDeactivePump) {
        //TODO: Timing ist nicht richtig. Geht schneller aus als erwartet
        if (pumpState && (millis() - lastTimePumpOn >= (minTimeActivePump*60000))) {
            turnPumpOff();
        }
    }
}

void PumpControl::updatePumpState(bool state) {
    if(state){
        turnPumpOn();
    } else {
        turnPumpOff();
    }
    
}

void PumpControl::turnPumpOn() {
    digitalWrite(pinPump, HIGH);
    pumpState = true;
}

void PumpControl::turnPumpOff() {
    digitalWrite(pinPump, LOW);
    pumpState = false;
}

bool PumpControl::isPumpActive() {
    return pumpState;
}

float PumpControl::getTemp1() {
    return sensorCollector.getTemp();
}

float PumpControl::getTemp2() {
    return sensorStorage.getTemp();
}