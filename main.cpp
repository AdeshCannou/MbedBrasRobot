#include "mbed.h"
#include "Serial.h"
#include "StepperMotor.h"

// Configure les broches pour le pilote A4988
DigitalOut dirPin(p5);
DigitalOut stepPin(p6);

// Configure la constante pour le nombre de pas par tour du moteur
const int stepsPerRevolution = 200;

Serial bt(p28, p27); // définir une connexion série pour le module Bluetooth HC-05
DigitalOut led1(LED1); // définir une sortie numérique pour la LED1
Serial pc(USBTX, USBRX);
DigitalOut electromagnet(p8);

int main() {
    while (1) {
        //electromagnet = 1;
        if (bt.readable()) { // Vérifier si des données sont disponibles
            char c = bt.getc(); // Lire le caractère reçu
            pc.putc(c);
            switch(c) {
                case 'H':
                    // code pour le caractère 'H'
                    break;
                case 'B':
                    // code pour le caractère 'B'
                    break;
                case 'G':
                    // code pour le caractère 'G'
                    led1 = 0;
                    break;
                case 'D':
                    // code pour le caractère 'D'
                    dirPin = 1;
                    led1 = 1;
                    for(int i=0; i<stepsPerRevolution; i++) {
                        stepPin = 1;
                        wait_us(2000);
                        stepPin = 0;
                        wait_us(2000);
                    }
                    break;
                case 'O':
                    // code pour le caractère 'O'
                    electromagnet = 1;
                    break;
                case 'F':
                    // code pour le caractère 'F'
                    electromagnet = 0;
                    break;
                default:
                    // code pour un caractère inconnu
                    break;
            }
        }
    }
}
