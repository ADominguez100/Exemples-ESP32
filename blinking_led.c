/*
  Project: Blink (El "Hello, World!" dels microcontroladors)
  Description: Fa parpellejar un LED connectat al pin 23.
*/

// Definim una constant per al pin on hem connectat el LED
const int LED_PIN = 23;

// La funció setup() s'executa un cop quan la placa arrenca
void setup()
{
  // Configurem el pin del LED com una SORTIDA (OUTPUT)
  pinMode(LED_PIN, OUTPUT);
}

// La funció loop() s'executa contínuament
void loop()
{
  // Definim les variables per obrir i tancar el LED
  int open_delay = 1000;
  int close_delay = 900;

  digitalWrite(LED_PIN, HIGH); // Envia 3.3V al pin (encén el LED)
  delay(open_delay);           // Espera 1000 mil·lisegons (1 segon)

  digitalWrite(LED_PIN, LOW); // Envia 0V al pin (apaga el LED)
  delay(close_delay);         // Espera 1 segon
}
