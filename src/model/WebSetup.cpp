#include "WebSetup.h"

WebSetup::WebSetup() : webport(80) { // Initialize webport with a default value, e.g., 80
  this->server = new WebServer(this->webport);
  // Serielle Kommunikation starten
  WiFi.begin(this->ssid, this->password);

  // Warte, bis die Verbindung hergestellt ist
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Verbinde mit WLAN...");
  }

  Serial.println("Verbunden mit WLAN!");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.localIP());

  // Routen definieren
  this->server->on("/", std::bind(&WebSetup::handleRoot, this));         // Wenn "/" aufgerufen wird, handleRoot() ausführen
  this->server->on("/events", std::bind(&WebSetup::handleSSE, this));    // Route für die SSE-Verbindung

  // Webserver starten
  this->server->begin();
  Serial.println("HTTP-Server gestartet.");
}

// Funktion, die die SSE-Verbindung verwaltet
void WebSetup::handleSSE() {
  // Setze den Header für SSE
  server->setContentLength(CONTENT_LENGTH_UNKNOWN);
  server->send(200, "text/event-stream");
  
  while (true) {
    // Hole die aktuelle Signalstärke (RSSI)
    int rssi = WiFi.RSSI();
    
    // Sende die Daten als SSE-Nachricht
    server->sendContent("data: " + String(rssi) + "\n\n");
    delay(1000);  // Aktualisiere alle 1 Sekunde

    // Verlasse die Schleife, wenn die Verbindung verloren geht
    if (!server->client().connected()) {
      break;
    }
  }
}

// Funktion, die die Hauptseite bereitstellt
void WebSetup::handleRoot() {
  String html = "<html><head><title>WLAN Empfangsanzeige</title></head><body>";
  html += "<h1>WLAN Empfangsanzeige</h1>";
  html += "<p>Signalstärke (RSSI): <span id='rssi'>Lade...</span> dBm</p>";
  html += "<script>";
  html += "const eventSource = new EventSource('/events');";
  html += "eventSource.onmessage = function(event) {";
  html += "document.getElementById('rssi').textContent = event.data;";
  html += "};";
  html += "</script>";
  html += "</body></html>";

  server->send(200, "text/html", html);
}



