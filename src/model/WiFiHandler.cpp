#include "WiFiHandler.h"

WiFiHandler::WiFiHandler(const char* ssid, const char* password) 
: ssid(ssid), password(password) {}

void WiFiHandler::connect() {
  WiFi.begin(this->ssid, this->password);
  
  unsigned long startAttemptTime = millis();
  const unsigned long timeout = 3000; // Timeout in Millisekunden (z.B. 30 Sekunden)

  // Warte, bis die Verbindung hergestellt ist oder das Timeout erreicht ist
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
    delay(1000);
    Serial.println("Verbinde mit WLAN...");
  }

  if (WiFi.status() == WL_CONNECTED) {
    this->ip = WiFi.localIP().toString();
    Serial.println("Verbunden mit WLAN!");
    Serial.print("IP-Adresse: ");
    Serial.println(this->ip);
  } else {
    throw ConnectionTimeoutException();
  }
}

String WiFiHandler::getIPadress() {
  return this->ip;
}

bool WiFiHandler::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}