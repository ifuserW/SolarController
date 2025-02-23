#include "WiFiHandler.h"

WiFiHandler::WiFiHandler(const char* ssid, const char* password) : ssid(ssid), password(password) { // Initialize webport with a default value, e.g., 80

}

void WiFiHandler::connect() {
  WiFi.begin(this->ssid, this->password);
  // TODO: Timeout einstellen! Warte, bis die Verbindung hergestellt ist
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Verbinde mit WLAN...");
  }
  this->ip = WiFi.localIP().toString();
  Serial.println("Verbunden mit WLAN!");
  Serial.print("IP-Adresse: ");
  Serial.println(this->ip);
}

String WiFiHandler::getIPadress() {
  return this->ip;
}
