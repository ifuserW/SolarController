#ifndef PUMPCONTROL_H
#define PUMPCONTROL_H

#include "PT1000.h"

class PumpControl {
public:
    PumpControl(const int tempdivForActivePump, 
        const int tempdivForDeactivePump, 
        const int minTimeActivePump, 
        const int maxTempStorage,
        const int pin0, 
        const int pin1, 
        const int pinPump);
    void controlPump();
    float getTemp1();
    float getTemp2();
    bool isPumpActive();

private:
    // -------------- PumpControl --------------
    const int tempdivForActivePump;
    const int tempdivForDeactivePump;
    const int minTimeActivePump;    // in minutes
    const int maxTempStorage;  // in °C
    // -------------- End PumpControl --------------

    const int pinPump;
    PT1000 sensorCollector;
    PT1000 sensorStorage;
    bool pumpState;
    unsigned long lastTimePumpOn;

    void turnPumpOn();
    void turnPumpOff();
    void updatePumpState(bool state);
};

#endif // PUMPCONTROL_H