#include "WebSetup.h"

WebSetup::WebSetup(const int webport) : webport(webport) { // Initialize webport with a default value, e.g., 80
  this->server = new WebServer(this->webport);
}

void WebSetup::start() {
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
  // Schreibe Daten in json-Format
  String jsonData = "{\"temp1\": " + String(temp1) + ", \"temp2\": \"" + String(temp2) + "\", \"pumpMode\": \"" + pumpMode + "\"}";
  // Sende die Daten als SSE-Nachricht
  server->sendContent("data: " + jsonData + "\n\n");
}

// Funktion, die die Hauptseite bereitstellt
void WebSetup::handleRoot() {
  String html = "<html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>WLAN Empfangsanzeige</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f4; color: #333; margin: 0; padding: 20px; }";
  html += "h1 { color: #007BFF; }";
  html += "p { font-size: 1.2em; background: white; padding: 10px; border-radius: 8px; display: inline-block; width: 80%; max-width: 400px; margin: 10px auto; }";
  html += "span { font-weight: bold; color: #d35400; }";
  html += "</style>";
  html += "</head><body>";
  html += "<h1>Thermische Solaranlage - Steuerung</h1>";
  html += "<p>Collector: <span id='temp1'>Lade...</span> &#176;C</p>";
  html += "<p>Storage: <span id='temp2'>Lade...</span> &#176;C</p>";
  html += "<p>Pumpe (Zustand): <span id='pumpMode'>Lade...</span></p>";
  html += "<script>";
  html += "const eventSource = new EventSource('/events');";
  html += "eventSource.onmessage = function(event) {";
  html += "const data = JSON.parse(event.data);";
  html += "document.getElementById('temp1').textContent = data.temp1;";
  html += "document.getElementById('temp2').textContent = data.temp2;";
  html += "document.getElementById('pumpMode').textContent = data.pumpMode;";
  html += "};";
  html += "</script>";
  html += "</body></html>";
  

  server->send(200, "text/html", html);
}

void WebSetup::handleClient(String temp1, String temp2, String pumpMode) {
  // Aktualisiere die Werte
  this->temp1 = temp1;
  this->temp2 = temp2;
  this->pumpMode = pumpMode;

  static unsigned long lastSSETime = 0;
  unsigned long currentTime = millis();

  // Sende SSE-Nachrichten alle 1000 ms
  if (currentTime - lastSSETime >= 1000) {
    this->server->handleClient();
    lastSSETime = currentTime;
  }
}
