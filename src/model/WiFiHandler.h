/*
    * LCDview.h
    * Date: 2024-11-28
    * Author: Dennis Golowatschjow
    * 
    * Description:
*/

#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <WiFi.h>
#include <exception>

class WiFiHandler {
    public:
        WiFiHandler(const char* ssid, const char* password);
        void connect();
        String getIPadress();
        bool isConnected();
    
        class ConnectionTimeoutException : public std::exception {
            public: virtual const char* what() const throw() {
                return "Verbindung zum WLAN fehlgeschlagen. Timeout erreicht.";
            }
      };
    
    private:
      const char* ssid;
      const char* password;
      String ip;
    };
    
#endif // WIFIHANDLER_H