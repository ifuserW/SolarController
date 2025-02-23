#ifndef PT1000_H
#define PT1000_H

#include <Arduino.h>

class PT1000 {
public:
    PT1000(const int pin);
    void readTemp();
    float getTemp();
    float getVoltage();

private:
    const int pin;
    float voltage;
    float temp;
};

#endif // PT1000_H