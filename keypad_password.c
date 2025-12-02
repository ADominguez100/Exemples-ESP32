// importa libreria Keypad
#include <Keypad.h>

// define numero de filas
const uint8_t ROWS = 4;
// define numero de columnas
const uint8_t COLS = 4;

// define la distribucion de teclas
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// pines correspondientes a las filas
uint8_t colPins[COLS] = { 16, 4, 2, 15 };
// pines correspondientes a las columnas
uint8_t rowPins[ROWS] = { 19, 18, 5, 17 };

// crea objeto con los parametros creados previamente
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//Array de chars (String) per introduir la contrasenya
char psswd[5] = "";
//Comptador per saber quin dígit estem establint
int cont = 0;
//Booleà per saber si la contrasenya està establerta
bool passwordSet = false;

void setup() {
  Serial.begin(9600);
  Serial.println("ESTABLEIX LA TEVA CONTRASENYA INICIAL");
  Serial.println("Introdueix 4 digits (0-9)");
  Serial.println("Prem la tecla 'A' per mostrar la contrasenya establerta.");
  Serial.println("Prem la tecla '*' per reestablir la contrasenya.");
  Serial.println("Prem la tecla '#' per confirmar la contrasenya.");
  Serial.println("----------------------------------------");
}

void loop() {
  if (cont >= 4 && !passwordSet) { //Si ja hem introduït els 4 dígits finalitzem String amb null (\0) i passem booleà a true
    psswd[4] = '\0';
    Serial.println("\nContrasenya establerta correctament.");
    passwordSet = true;
    return; //Finalitzem loop;
  }
  
  char key = keypad.getKey();
  
  if (!key) {
    return;
  }
  
  if (key >= '0' && key <= '9') { //Comprovem que la tecla premuda és un dígit vàlid
    if (cont < 4) { //Si encara no tenim 4 dígits introduïm i mostrem un '*', sino avisem
      psswd[cont] = key;
      cont++;
      psswd[cont] = '\0';
      Serial.print("*");
    } else {
      Serial.println("\nJa tens 4 digits. Prem '#' per confirmar o '*' per reiniciar.");
    }
  }
  else if (key == 'A') { //Si premem A, printem la contrasenya per terminal
    if (cont > 0) {
      Serial.print("\nContrasenya actual: ");
      for (int i = 0; i < cont; i++) {
        Serial.print(psswd[i]);
      }
      Serial.println();
    } else {
      Serial.println("\nEncara no has introduit cap digit.");
    }
  }
  else if (key == '*') { //Si la tecla és '*', fem reset de la contrasenya amb un mètode
    resetPassword();
    Serial.println("\nContrasenya reiniciada. Introdueix 4 nous digits (0-9):");
  }
  else if (key == '#') { //Si premem '#' confirmem contrasenya i la establim. Si encara no tenim 4 digits avisem.
    if (cont == 4) {
      psswd[4] = '\0';
      Serial.print("\nContrasenya confirmada: ");
      Serial.println(psswd);
      passwordSet = true;
    } else {
      Serial.print("\nFalten digits. Portes ");
      Serial.print(cont);
      Serial.println(" de 4.");
    }
  }
  else if (key == 'B' || key == 'C' || key == 'D') { //Si premem qualsevol de les altres avisem que no fan res.
    Serial.println("\nTecla no permesa. Només pots introduir digits (0-9).");
  }
}

void resetPassword() { //Mètode resetPassword per esborrarla completament
  for (int i = 0; i < 5; i++) {
    psswd[i] = '\0';
  }
  cont = 0;
  passwordSet = false;
}