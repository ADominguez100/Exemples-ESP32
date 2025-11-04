// =============================
//   VARIABLES MÉS COMUNS EN C
//  Per a ESP32 amb Arduino IDE
// =============================

#include <stdio.h>
#include <stdbool.h>

int main() {
    
    // char - Caràcter individual
    // Emmagatzema una lletra, dígit o símbol ASCII
    // S'utilitza per representar text caràcter a caràcter, llegir entrada serial, mostrar caràcters en pantalles
    char comando = 'A';
    printf("Comando rebut: %c\n", comando);
    // Exemple ESP32: Serial.read() retorna un char quan rep dades pel port serial

    // Els caràcters ens permeten fer una cadena. Si inicialitzem la variable com a un 'array' de caràcters,
    // podem crear el que es coneix en altres llenguatges com String.
    // En aquest cas la cadena utilitza %s com a especificador de format (format specifier) en el print.
    char nom_xarxa[] = "ESP32_Sensor";
    printf("Nom del dispositiu: %s\n", nom_xarxa);
    // Exemple ESP32: WiFi.begin(nom_xarxa, password) per connectar a una xarxa WiFi
    
    
    // int - Enter
    // Emmagatzema números enters positius i negatius
    // S'utilitza per comptadors, índexs, valors de sensors digitals, pins GPIO
    // EXTRA: En C es pot emmagatzemar un enter que només accepti números positius (0 en endavant). Només fa falta inicialitzar-ho com unsigned int.
    int pin_led = 2;
    printf("Pin del LED: %d\n", pin_led);
    // Exemple ESP32: pinMode(pin_led, OUTPUT) per configurar el pin GPIO 2 com a sortida
    // Exemple ESP32: int temperatura_sensor = analogRead(34) per llegir un sensor analògic
       
    
    // short - Enter curt
    // Emmagatzema números enters més petits que int
    // S'utilitza quan volem estalviar memòria i sabem que els valors seran petits, ideal per valors de sensors compactes
    short temperatura = -15;
    printf("Temperatura: %hd°C\n", temperatura);
    // Exemple ESP32: short offset_calibracio = -5 per ajustar lectures d'un sensor de temperatura
    
    
    // long - Enter llarg
    // Emmagatzema números enters molt grans
    // S'utilitza per timestamps, comptadors de mil·lisegons, valors acumulatius
    // Quan li donem valor a una variable de tipus long s'ha d'afegir el caràcter 'L' al final d'aquest. Això és perquè el compilador sinó interpreta el valor
    // com un int, i al ser major als límits acceptats per la variable int, donarà error si no indiquem amb la 'L' que es tracta d'un long.
    long temps_inici = 1500000000L;
    printf("Timestamp: %ld\n", temps_inici);
    // Exemple ESP32: long temps = millis() retorna els mil·lisegons des que l'ESP32 va arrencar
    // Exemple ESP32: unsigned long interval = 5000UL per definir un interval de 5 segons (5000ms)
    
    
    // float - Número decimal de precisió simple
    // Emmagatzema números amb decimals (aproximadament 6-7 dígits de precisió)
    // S'utilitza per mesures de sensors analògics, càlculs de voltatge, temperatura, humitat
    float voltatge = 3.3f;
    printf("Voltatge: %.2fV\n", voltatge);
    // Exemple ESP32: float temp_DHT = dht.readTemperature() per llegir temperatura d'un sensor DHT22
    // Exemple ESP32: float bateria = (analogRead(35) / 4095.0) * 3.3 per calcular el voltatge d'una bateria
    
    
    // double - Número decimal de precisió doble
    // Emmagatzema números amb més decimals que float (15-16 dígits de precisió)
    // S'utilitza quan necessitem més precisió en càlculs GPS, coordenades geogràfiques, càlculs científics complexos
    double latitud = 41.387917;
    printf("Latitud GPS: %.6f\n", latitud);
    // Exemple ESP32: double lat = gps.location.lat() per obtenir coordenades GPS amb alta precisió
    // Exemple ESP32: double distancia = calcularDistanciaGPS(lat1, lon1, lat2, lon2) per càlculs geogràfics precisos
    
    
    // bool - Booleà
    // Emmagatzema true (1) o false (0)
    // S'utilitza per estats de pins, condicions, flags d'esdeveniments, estats de connexió
    bool led_ences = true;
    if (led_ences) {
        printf("LED encès\n");
    }
    // Exemple ESP32: bool estat_boto = digitalRead(pin_boto) per llegir l'estat d'un botó (HIGH/LOW)
    // Exemple ESP32: bool wifi_connectat = (WiFi.status() == WL_CONNECTED) per verificar connexió WiFi
    
    
    // const - Constant (valor immutable)
    // Defineix un valor que NO pot canviar durant l'execució
    // S'utilitza per pins fixos, temps d'espera, límits de sensors, configuracions que no canvien
    const int PIN_SENSOR = 34;
    int lectura = 1024; // Simulació de lectura
    printf("Lectura del sensor en pin %d: %d\n", PIN_SENSOR, lectura);
    // Exemple ESP32: const int TRIGGER_PIN = 5 per definir el pin del sensor ultrasònic que no canviarà
    // Exemple ESP32: const float FACTOR_CONVERSIO = 0.0322f per convertir valors ADC a voltatge (3.3V / 1024)
    // Exemple ESP32: const unsigned long TEMPS_DEBOUNCE = 50UL per definir temps anti-rebot de botons
    
    
    return 0;
}