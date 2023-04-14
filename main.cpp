#include "mbed.h"
#include "Serial.h"

// Configure la constante pour le nombre de pas par tour du moteur
const int stepsPerRevolution = 25;
DigitalOut led1(LED1);

//------------------------------
DigitalOut stepPin(p9);
// M1 -- Configure les broches pour le pilote A4988 
DigitalOut dirPinM1(p6);
DigitalIn stopM1(p23);


// M2 -- Configure les broches pour le pilote A4988 
DigitalOut dirPinM2(p10);

// M3 -- Configure les broches pour le pilote A4988 
DigitalOut dirPinM3(p24);

//-----------------------------
Serial bt(p28, p27); // définir une connexion série pour le module Bluetooth HC-05
Serial pc(USBTX, USBRX);
//------------------------------

//------------------------------
DigitalOut electromagnet(p19);
//------------------------------

int main() {
    while (1) {
        // for(int i=0; i<500; i++) {
        //                 stepPin = 1;
        //                 wait_us(2000);
        //                 stepPin = 0;
        //                 wait_us(2000);
        //             }
        if (bt.readable()) { // Vérifier si des données sont disponibles
            char c = bt.getc(); // Lire le caractère reçu
            pc.putc(c);
            switch(c) {
                case 'F':
                    break;
                case 'B':
                    break;
                case 'L':
                    // code pour le caractère 'H'
                    break;
                case 'R':
                    // code pour le caractère 'B'
                    break;
                case 'U':
                    led1=1;
                    // code pour le caractère 'G'
                    dirPinM1 = 1;
                    dirPinM2 = 1;
                    dirPinM3 = 1;
                    for(int i=0; i<stepsPerRevolution; i++) {
                        stepPin = 1;
                        wait_us(2000);
                        stepPin = 0;
                        wait_us(2000);
                    }
                    break;
                case 'D':
                    // code pour le caractère 'D'
                    led1=0;
                    dirPinM1 = 0;
                    dirPinM2 = 0;
                    dirPinM3 = 0;
                    for(int i=0; i<stepsPerRevolution; i++) {
                        stepPin = 1;
                        wait_us(2000);
                        stepPin = 0;
                        wait_us(2000);
                    }
                    break;
                case 'M':
                    // code pour le caractère 'O'
                    electromagnet = 1;
                    break;
                case 'W':
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

