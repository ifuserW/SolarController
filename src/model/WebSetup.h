/*
    * LCDview.h
    * Date: 2024-11-28
    * Author: Dennis Golowatschjow
    * 
    * Description:
    * This class is used to display the temperature and the pump mode on a LCD display in a specific format.
    * TODO: Schau ob es eine bessere möglichkeit gibt mit Vererbung (view nur implementieren, erben von LiquidCrystal_I2C, wie java)
*/

#ifndef WEBSETUP_H
#define WEBSETUP_H

#include <WiFi.h>
#include <WebServer.h>

class WebSetup {
private:
    const char* ssid;
    const char* password;
    const int webport;
    WebServer* server;
    String temp1;
    String temp2;
    String pumpMode;
    String ip;
    
public:
    WebSetup(const char* ssid, const char* password, const int webport);
    void connect();
    void handleRoot();
    void handleSSE();
    void handleClient(String temp1, String temp2, String pumpMode);
    String getIPadress();
};

#endif // WEBSETUP_H