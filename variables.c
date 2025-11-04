// ============================
//  VARIABLES MÁS COMUNES EN C
// ============================

#include <stdio.h>
#include <stdbool.h>

int main() {
    
    // char - Caràcter individual
    // Emmagatzema una lletra, dígit o símbol ASCII
    // S'utilitza per representar text caràcter a caràcter
    char letra = 'A';
    printf("Caràcter: %c\n", letra);

    // Els caràcters ens permeten fer una cadena. Si inicialitzem la variable com a un 'array' de caracters,
    // podem crear el que es coneix en altres llenguatjes com String.
    // En aquest cas la cadena utilitza %s com a especificador de format (format specifier) en el print.
    char nom[] = "Adrià";
    printf("El meu nom és %s\n", nom);
    
    
    // int - Enter
    // Emmagatzema números enters positius i negatius
    // S'utilitza per comptadors, índexs, quantitats sense decimals
    // EXTRA: En C es pot emmagatzemar un enter que només accepti números positius (0 en endavant). Només fa falta inicialitzar-ho com unsigned int.
    int edat = 25;
    printf("Edat: %d anys\n", edat);
       
    
    // short - Enter curt
    // Emmagatzema números enters més petits que int
    // S'utilitza quan volem estalviar memòria i sabem que els valors seran petits
    short temperatura = -15;
    printf("Temperatura: %hd°C\n", temperatura);
    
    
    // long - Enter llarg
    // Emmagatzema números enters molt grans
    // S'utilitza per números que poden superar el rang d'int
    // Quan li donem valor a una variable de tipus long s'ha d'afegir el caràcter 'L' al final d'aquest. Això és perquè el compilador sino interpreta el valor
    // com un int, i al ser major als límits acceptats per la variable int, donarà error si no indiquem amb la 'L' que es tracta d'un long.
    long poblacio_mundial = 8000000000L;
    printf("Població mundial: %ld\n", poblacio_mundial);
    
    
    // float - Número decimal de precisió simple
    // Emmagatzema números amb decimals (aproximadament 6-7 dígits de precisió)
    // S'utilitza per mesures, càlculs científics, preus amb decimals
    float preu = 19.99f;
    printf("Preu: %.2f€\n", preu);
    
    
    // double - Número decimal de precisió doble
    // Emmagatzema números amb més decimals que float (15-16 dígits de precisió)
    // S'utilitza quan necessitem més precisió en càlculs científics o financers
    double pi = 3.141592653589793;
    printf("Pi: %.15f\n", pi);
    
    
    // bool - Booleà
    // Emmagatzema true (1) o false (0)
    // S'utilitza per condicions, flags, estats on/off
    bool es_major_edat = true;
    if (es_major_edat) {
        printf("És major d'edat\n");
    }
    
    
    // const - Constant (valor immutable)
    // Defineix un valor que NO pot canviar durant l'execució
    // S'utilitza per valors fixos com IVA, límits, configuracions, números en càlculs ja coneguts com PI
    const float IVA = 0.21f;
    float preu_base = 100.0f;
    float preu_amb_iva = preu_base * (1 + IVA);
    printf("Preu amb IVA: %.2f€\n", preu_amb_iva);
    
    
    return 0;
}