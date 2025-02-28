#include "PT1000.h"

PT1000::PT1000(const int pin) : pin(pin) {
    // Constructor implementation
}

void PT1000::readTemp() {
    this->voltage = analogRead(pin) * (3.3 / 4095.0);
    // this->temp = (this->voltage * 212.904) + 820;    This displays the resistance
    this->temp = this->voltage * 95.99815 - 46.15;
}

float PT1000::getTemp() {
    return this->temp;
}

float PT1000::getVoltage() {
    return this->voltage;
}
