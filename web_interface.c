/*
 * ESP32 Web Server - LED Virtual
 * Modificado para simular LED sin hardware físico
 */
#include <DIYables_ESP32_WebServer.h>

int LED_state = LOW;
bool blinking = false;  // Nueva variable para controlar parpadeo
unsigned long previousMillis = 0;
const long blinkInterval = 500;  // Parpadeo cada 500ms

// WiFi credentials
const char WIFI_SSID[] = "iPhone de Adria";
const char WIFI_PASSWORD[] = "12345678";

// Create web server instance
DIYables_ESP32_WebServer server;

// Page handlers
String getHTML() {
  String html = "<!DOCTYPE HTML>";
  html += "<html>";
  html += "<head>";
  html += "<link rel='icon' href='data:,'>";
  html += "<meta http-equiv='refresh' content='1'>";  // Auto-refresh cada 1 segundo
  html += "<style>";
  html += "body { font-family: Arial; text-align: center; margin-top: 50px; }";
  html += ".led-indicator { width: 100px; height: 100px; border-radius: 50%; margin: 20px auto; ";
  html += "border: 3px solid #333; }";
  html += ".led-on { background-color: #00ff00; box-shadow: 0 0 20px #00ff00; }";
  html += ".led-off { background-color: #333; }";
  html += ".led-blink { background-color: #ffaa00; box-shadow: 0 0 20px #ffaa00; }";
  html += "a { display: inline-block; padding: 15px 30px; margin: 10px; ";
  html += "background-color: #4CAF50; color: white; text-decoration: none; border-radius: 5px; }";
  html += "a:hover { background-color: #45a049; }";
  html += ".blink-btn { background-color: #ff9800; }";
  html += ".blink-btn:hover { background-color: #e68900; }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Control de LED Virtual</h1>";
  
  // Indicador visual del LED
  html += "<div class='led-indicator ";
  if (blinking)
    html += "led-blink";
  else if (LED_state == HIGH)
    html += "led-on";
  else
    html += "led-off";
  html += "'></div>";
  
  html += "<p style='font-size: 24px;'>Estado del LED: <span style='color: ";
  if (blinking) {
    html += "orange; font-weight: bold;'>PARPADEANDO";
  } else if (LED_state == LOW) {
    html += "red; font-weight: bold;'>OFF";
  } else {
    html += "green; font-weight: bold;'>ON";
  }
  html += "</span></p>";
  
  html += "<a href='/led1/on'>Encender</a>";
  html += "<a href='/led1/off'>Apagar</a>";
  html += "<a href='/led1/blink' class='blink-btn'>Parpadeig</a>";
  html += "</body>";
  html += "</html>";
  return html;
}

// home page
void handleHome(WiFiClient& client, const String& method, const String& request, const QueryParams& params, const String& jsonData) {
  Serial.println("ESP32 Web Server: Nueva petición recibida");
  server.sendResponse(client, getHTML().c_str());
}

void handleLedOn(WiFiClient& client, const String& method, const String& request, const QueryParams& params, const String& jsonData) {
  Serial.println("ESP32 Web Server: LED ENCENDIDO");
  blinking = false;
  LED_state = HIGH;
  server.sendResponse(client, getHTML().c_str());
}

void handleLedOff(WiFiClient& client, const String& method, const String& request, const QueryParams& params, const String& jsonData) {
  Serial.println("ESP32 Web Server: LED APAGADO");
  blinking = false;
  LED_state = LOW;
  server.sendResponse(client, getHTML().c_str());
}

void handleLedBlink(WiFiClient& client, const String& method, const String& request, const QueryParams& params, const String& jsonData) {
  Serial.println("ESP32 Web Server: LED PARPADEANDO");
  blinking = true;
  server.sendResponse(client, getHTML().c_str());
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  Serial.println("ESP32 Web Server - LED Virtual");
  Serial.println("==============================");
  
  // Configure routes
  server.addRoute("/", handleHome);
  server.addRoute("/led1/on", handleLedOn);
  server.addRoute("/led1/off", handleLedOff);
  server.addRoute("/led1/blink", handleLedBlink);  // Nueva ruta
  
  // Start web server with WiFi connection
  server.begin(WIFI_SSID, WIFI_PASSWORD);

  delay(2000);
  Serial.print("Dirección IP del ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
  
  // Lógica de parpadeo
  if (blinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      LED_state = !LED_state;  // Alternar estado
      Serial.print("Parpadeig: ");
      Serial.println(LED_state == HIGH ? "ON" : "OFF");
    }
  }
}