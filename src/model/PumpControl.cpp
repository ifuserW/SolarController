#include "PumpControl.h"

PumpControl::PumpControl(const int tempdivForActivePump, 
    const int tempdivForDeactivePump, 
    const int minTimeActivePump, 
    const int maxTempCollector,
    const int pin0, 
    const int pin1, 
    const int pinPump)
    : tempdivForActivePump(tempdivForActivePump), 
    tempdivForDeactivePump(tempdivForDeactivePump), 
    minTimeActivePump(minTimeActivePump), 
    maxTempCollector(maxTempCollector),
    sensorCollector(pin0),  // Initialize PT1000 sensors here
    sensorStorage(pin1),    // Initialize PT1000 sensors here
    pinPump(pinPump),    // Initialize pump control settings here
    pumpState(false) {

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
    
    // TODO: implement pump control logic
    turnPumpOff();
    // if (sensorCollector.getTemp() > maxTempCollector) {
    //     turnPumpOff();
    // } else if (tempCollector > tempdivForActivePump) {
    //     turnPumpOn();
    // } else if (tempCollector < tempdivForDeactivePump) {
    //     turnPumpOff();
    // }

    // Add logic to update pumpState based on sensor readings
    // Example:
    // float temp1 = sensor1.readTemperature();
    // float temp2 = sensor2.readTemperature();
    // pumpState = (temp1 > threshold) && (temp2 > threshold);
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