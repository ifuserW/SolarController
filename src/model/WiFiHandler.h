/*
    * LCDview.h
    * Date: 2024-11-28
    * Author: Dennis Golowatschjow
    * 
    * Description:
    * This class is used to display the temperature and the pump mode on a LCD display in a specific format.
    * TODO: Schau ob es eine bessere möglichkeit gibt mit Vererbung (view nur implementieren, erben von LiquidCrystal_I2C, wie java)
*/

#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <WiFi.h>

class WiFiHandler {
private:
    const char* ssid;
    const char* password;
    String ip;
    
public:
    WiFiHandler(const char* ssid, const char* password);
    void connect();
    String getIPadress();
};

#endif // WIFIHANDLER_H