#include "LCDview.h"
#include <LiquidCrystal_I2C.h>

// Initialize the library with the numbers of the interface pins

LCDview::LCDview(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows) : lcd(lcd_addr, lcd_cols, lcd_rows) {
    // TODO: BETTER Initialize the LCD
    this->lcd.init();
    this->lcd.backlight();
    // Print a message to the LCD.
    this->lcd.print("Startup Controller!");
}

void LCDview::setTemp1(const String& temp) {
    int pos = this->_output.indexOf("Temp1:") + 6;
    this->_output = this->_output.substring(0, pos) + temp;
    this->update();
}
void LCDview::setTemp2(const String& temp) {
    int pos = this->_output.indexOf("Temp2:") + 6;
    this->_output = this->_output.substring(0, pos) + temp;
    this->update();
}
void LCDview::setPumpMode(const String& mode) {
    int pos = this->_output.indexOf("Pumpe:") + 6;
    this->_output = this->_output.substring(0, pos) + mode;
    this->update();
}


void LCDview::update() {
    this->clear();
    this->print(String(this->_output.c_str()));
}

void LCDview::clear() {
    this->lcd.clear();
}

void LCDview::print(const String& text) {
    // this->lcd.print("wird geändert");
    this->lcd.clear();
    this->lcd.print(text.c_str());
}

