#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  
  // Conectar a WiFi
  WiFi.begin("iPhone de Adria", "12345678");
  Serial.print("Conectando a WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConectado!");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    http.begin("https://v3.football.api-sports.io/players/profiles?player=762");
    http.addHeader("x-apisports-key", "1556498735047342efb22ea564464b24");
    
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      
      Serial.println("Tamaño de respuesta: " + String(payload.length()) + " bytes");
      Serial.println("Primeros 500 caracteres:");
      Serial.println(payload.substring(0, 500));
      
      // Aumenta el tamaño del documento
      DynamicJsonDocument doc(16384); // Prueba con 16KB
      DeserializationError error = deserializeJson(doc, payload);
      
      if (error) {
        Serial.print("Error parseando JSON: ");
        Serial.println(error.c_str());
        return;
      }
      
      serializeJsonPretty(doc, Serial);
    }
    
    http.end();
  }
  
  delay(60000);
}