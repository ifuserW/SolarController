#include "LCDview.h"
#include <LiquidCrystal_I2C.h>

// Initialize the library with the numbers of the interface pins

LCDview::LCDview(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows) : lcd(lcd_addr, lcd_cols, lcd_rows) {
    // TODO: BETTER Initialize the LCD
    this->lcd.init();
    this->lcd.backlight();
    // Print a message to the LCD.
    this->lcd.print("Startup Controller!");
    this->clear();
}

void LCDview::setTemp1(const String& temp) {
    this->lcd.setCursor(0, 0); // Set cursor to the first row
    this->lcd.print("                "); // Clear the line by printing spaces
    this->lcd.setCursor(0, 0); // Reset cursor to the beginning of the line
    this->lcd.print("Temp1: " + temp); // Print the new text
}

void LCDview::setTemp2(const String& temp) {
    this->lcd.setCursor(0, 1); // Set cursor to the first row
    this->lcd.print("                "); // Clear the line by printing spaces
    this->lcd.setCursor(0, 1); // Reset cursor to the beginning of the line
    this->lcd.print("Temp2: " + temp); // Print the new text
}
void LCDview::setPumpMode(const String& mode) {
    this->lcd.setCursor(0, 2); // Set cursor to the first row
    this->lcd.print("                "); // Clear the line by printing spaces
    this->lcd.setCursor(0, 2); // Reset cursor to the beginning of the line
    this->lcd.print("Pump: " + mode); // Print the new text
}

void LCDview::clear() {
    this->lcd.clear();
}

void LCDview::print(const String& text) {
    // this->lcd.print("wird geändert");
    this->lcd.clear();
    this->lcd.print(text.c_str());
}

void LCDview::print(const String& text, int x, int y) {
    this->lcd.setCursor(x, y);
    this->lcd.print(text.c_str());
}

void LCDview::printIP(const String& ip) {
    this->lcd.setCursor(0, 3);
    this->lcd.print("IP: ");
    this->lcd.print(ip);
}