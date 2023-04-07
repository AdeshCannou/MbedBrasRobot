#include "mbed.h"
#include "Serial.h"
#include "StepperMotor.h"

// Configure la constante pour le nombre de pas par tour du moteur
const int stepsPerRevolution = 25;
int angle = 0;

//------------------------------
DigitalOut stepPin(p5);
// M1 -- Configure les broches pour le pilote A4988 
DigitalOut dirPinM1(p6);
DigitalOut nSleepM1(p7);
DigitalOut nresetM1(p8);
// M2 -- Configure les broches pour le pilote A4988 
DigitalOut dirPinM2(p10);
DigitalOut nresetM2(p12);
DigitalOut nSleepM2(p11);
// M3 -- Configure les broches pour le pilote A4988 
DigitalOut dirPinM3(p24);
DigitalOut nresetM3(p26);
DigitalOut nSleepM3(p25);
//------------------------------


//------------------------------
DigitalIn stopM1(p23);
DigitalIn stopM2(p22);
DigitalIn stopM3(p21);
//------------------------------



//-----------------------------
Serial bt(p28, p27); // définir une connexion série pour le module Bluetooth HC-05
Serial pc(USBTX, USBRX);
//------------------------------


//------------------------------
DigitalOut electromagnet(p8);
//------------------------------

bool motorRunning = false; // moteur






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
                    dirPinM1 = 0;
                    for(int i=0; i<stepsPerRevolution; i++) {
                        stepPin = 1;
                        wait_us(2000);
                        stepPin = 0;
                        wait_us(2000);
                    }
                    break;
                case 'D':
                    // code pour le caractère 'D'
                    dirPinM1 = 1;
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
