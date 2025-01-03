/*
    * LCDview.h
    * Date: 2024-11-28
    * Author: Dennis Golowatschjow
    * 
    * Description:
    * This class is used to display the temperature and the pump mode on a LCD display in a specific format.
    * TODO: Schau ob es eine bessere möglichkeit gibt mit Vererbung (view nur implementieren, erben von LiquidCrystal_I2C, wie java)
*/

#ifndef LCDVIEW_H
#define LCDVIEW_H

#include "view.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCDview : public View {
private:
    LiquidCrystal_I2C lcd;

public:
    // lcd_addr: I2C address of the LCD, lcd_cols: number of columns, lcd_rows: number of rows
    LCDview(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void setTemp1(const String &temp) override;
    void setTemp2(const String& temp) override;
    void setPumpMode(const String& mode) override;
    void clear();
    void print(const String& text);
};

#endif // LCDVIEW_H