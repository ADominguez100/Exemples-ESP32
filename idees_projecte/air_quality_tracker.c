#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

// Configuración WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// API Key de OpenWeatherMap (regístrate en https://openweathermap.org/api)
const char* apiKey = "a954ce8ef9522cbee163434bc4ce56a8";

// Coordenadas de tu ciudad (ejemplo: Calafell)
const float lat = 41.1969;
const float lon = 1.5669;

// LCD 16x2 en dirección I2C 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin del potenciómetro (simula sensor de calidad interior)
const int potPin = 34;

void setup() {
  Serial.begin(115200);
  
  // Configurar pin analógico
  pinMode(potPin, INPUT);
  
  // Inicializar LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi");
  
  // Conectar WiFi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConectado a WiFi!");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi OK!");
  delay(2000);
}

void loop() {
  // Leer sensor interior (potenciómetro)
  int valorPot = analogRead(potPin); // 0-4095
  int calidadInterior = map(valorPot, 0, 4095, 0, 100); // Convertir a 0-100
  
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Construir URL de la API
    String url = "http://api.openweathermap.org/data/2.5/air_pollution?lat=" + 
                 String(lat, 4) + "&lon=" + String(lon, 4) + "&appid=" + apiKey;
    
    Serial.println("\n===== CONSULTANDO API =====");
    http.begin(url);
    
    int httpCode = http.GET();
    
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      
      DynamicJsonDocument doc(2048);
      DeserializationError error = deserializeJson(doc, payload);
      
      if (!error) {
        // Extraer datos de calidad del aire exterior
        int aqi = doc["list"][0]["main"]["aqi"]; // Índice 1-5
        float pm25 = doc["list"][0]["components"]["pm2_5"];
        
        // Convertir AQI (1-5) a puntuación (100-0)
        int calidadExterior = map(aqi, 1, 5, 100, 0);
        
        // Mostrar en Serial
        Serial.println("EXTERIOR (API):");
        Serial.print("  Puntuacion: ");
        Serial.print(calidadExterior);
        Serial.println("/100");
        Serial.print("  PM2.5: ");
        Serial.println(pm25);
        
        Serial.println("\nINTERIOR (Sensor):");
        Serial.print("  Puntuacion: ");
        Serial.print(calidadInterior);
        Serial.println("/100");
        
        // COMPARACIÓN
        int diferencia = calidadExterior - calidadInterior;
        Serial.println("\nCOMPARACION:");
        Serial.print("  Diferencia: ");
        Serial.println(diferencia);
        
        // Mostrar en LCD - Línea 1
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ext:");
        lcd.print(calidadExterior);
        lcd.print(" Int:");
        lcd.print(calidadInterior);
        
        // Mostrar en LCD - Línea 2 (Recomendación)
        lcd.setCursor(0, 1);
        if (diferencia > 15) {
          lcd.print("VENTILAR!");
          Serial.println("  >> RECOMENDACION: Abre ventanas!");
        } else if (diferencia < -15) {
          lcd.print("CERRAR VENTANAS");
          Serial.println("  >> RECOMENDACION: Cierra ventanas!");
        } else {
          lcd.print("Todo OK");
          Serial.println("  >> RECOMENDACION: Todo correcto");
        }
        
      } else {
        Serial.println("Error parseando JSON");
        lcd.clear();
        lcd.print("Error JSON");
      }
      
    } else {
      Serial.print("Error HTTP: ");
      Serial.println(httpCode);
      lcd.clear();
      lcd.print("Error API");
    }
    
    http.end();
  }
  
  delay(10000); // Actualizar cada 10 segundos (para que veas cambios del potenciómetro)
}