#include "mbed.h"
#include "Serial.h"

Serial bt(p28, p27); // définir une connexion série pour le module Bluetooth HC-05
DigitalOut led1(LED1); // définir une sortie numérique pour la LED1
Serial pc(USBTX, USBRX);
DigitalOut electromagnet(p8);

int main() {
    while (1) {
        if (bt.readable()) { // Vérifier si des données sont disponibles
            char c = bt.getc(); // Lire le caractère reçu
            pc.putc(c);
            if (c == 'H') { // Si le caractère reçu est 'H' pour "haut"
                
            } else if (c == 'B') { // Si le caractère reçu est 'B' pour "bas"
                
            } else if (c == 'G') { // Si le caractère reçu est 'G' pour "gauche"
                
            } else if (c == 'D') { // Si le caractère reçu est 'D' pour "droite"
                
            } else if (c == 'O') { // Si le caractère reçu est 'O'
                led1 = 1;
                electromagnet = 1;
            } else if (c == 'F') { // Si le caractère reçu est 'F'
                led1 = 0;
                electromagnet = 0;
            }
        }
    }
}
