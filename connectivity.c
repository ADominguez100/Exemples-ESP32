#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String url = "https://www.positive-api.online/phrase/esp";

void setup() {
  Serial.begin(115200);
  delay(1000); // Pequeña pausa para estabilizar el serial
  
  Serial.println("\n=== INICIO DEL PROGRAMA ===");
  
  WiFi.begin(ssid, password);

  Serial.print("Connectant-se al WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✓ WiFi connectat correctament!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------");

  Serial.println("Obtenint resposta de la API...");

  HTTPClient http;
  http.begin(url);

  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {
    Serial.println("----------------------------");
    Serial.print("✓ HTTP Response Code: ");
    Serial.println(httpResponseCode);
    Serial.println("----------------------------");
    
    String payload = http.getString();
    Serial.println("RESPOSTA DE L'API:");
    Serial.println(payload);
    Serial.println("----------------------------");
  }
  else {
    Serial.println("----------------------------");
    Serial.print("✗ Error code: ");
    Serial.println(httpResponseCode);
    Serial.println("No s'ha pogut obtenir la resposta :-(");
    Serial.println("----------------------------");
  }
  
  http.end(); // Liberar recursos
  Serial.println("\n=== PROGRAMA FINALITZAT ===");
}

void loop() {
  delay(100);
}