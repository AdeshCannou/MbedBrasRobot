#include "mbed.h"
#include "Serial.h"
#include "mouvement.h"

#define OUT_OF_BOUNDS -1
#define ARM_AT_THE_TOP -2
#define MAGNET_BELOW -3

// Configure la constante pour le nombre de pas par tour du moteur
const int stepsPerRevolution = 25;
int angle = 0;
double position[2] = {0, 0};

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

void rotate_motor1(int steps) {
    nSleepM1 = 0;
    nSleepM2 = 1;
    nSleepM3 = 1;

    if(steps < 0) {
        dirPinM1 = 0;
        steps = -steps;
    } else {
        dirPinM1 = 1;
    }

    for(int i = 0; i < steps; i++) {
        if (stopM1 || stopM2 || stopM3) {
            break;
        }
        stepPin = 1;
        wait_us(2000);
        stepPin = 0;
        wait_us(2000);
    }
}

void rotate_motor2(int steps) {
    nSleepM1 = 1;
    nSleepM2 = 0;
    nSleepM3 = 1;

    if(steps < 0) {
        dirPinM2 = 0;
        steps = -steps;
    } else {
        dirPinM2 = 1;
    }

    for(int i = 0; i < steps; i++) {
        if (stopM1 || stopM2 || stopM3) {
            break;
        }
        stepPin = 1;
        wait_us(2000);
        stepPin = 0;
        wait_us(2000);
    }
}

void rotate_motor3(int steps) {
    nSleepM1 = 1;
    nSleepM2 = 1;
    nSleepM3 = 0;

    if(steps < 0) {
        dirPinM3 = 0;
        steps = -steps;
    } else {
        dirPinM3 = 1;
    }

    for(int i = 0; i < steps; i++) {
        if (stopM1 || stopM2 || stopM3) {
            break;
        }
        stepPin = 1;
        wait_us(2000);
        stepPin = 0;
        wait_us(2000);
    }
}

void init_arm() {
    while(!stopM1 || !stopM2 || !stopM3) {
        nSleepM1 = stopM1;
        nSleepM2 = stopM2;
        nSleepM3 = stopM3;

        stepPin = 1;
        wait_us(2000);
        stepPin = 2;
        wait_us(2000);
    }
}

int main() {
    init_arm();
    double x, y;

    while (1) {
        if (bt.readable()) { // Vérifier si des données sont disponibles
            char c = bt.getc(); // Lire le caractère reçu
            pc.putc(c);
            switch(c) {
                case 'F':
                    // code pour le caractère 'F'
                    x = position[0];
                    y = position[1] + 1;
                    if(norm({x, y}) < RADIUS-P_LENGTH) {
                        position[1] = y;
                        auto m = computeMove({x,y});

                        rotate_motor1(distanceToSteps(m[0]));
                        rotate_motor2(distanceToSteps(m[1]));
                        rotate_motor3(distanceToSteps(m[2]));

                    }
                    break;
                case 'B':
                    // code pour le caractère 'B'
                    x = position[0];
                    y = position[1] - 1;
                    if(norm({x, y}) < RADIUS-P_LENGTH) {
                        position[1] = y;
                        auto m = computeMove({x,y});

                        rotate_motor1(distanceToSteps(m[0]));
                        rotate_motor2(distanceToSteps(m[1]));
                        rotate_motor3(distanceToSteps(m[2]));
                        
                    }
                    break;
                case 'L':
                    // code pour le caractère 'L'
                    x = position[0] - 1;
                    y = position[1];
                    if(norm({x, y}) < RADIUS-P_LENGTH) {
                        position[0] = x;
                        auto m = computeMove({x,y});

                        rotate_motor1(distanceToSteps(m[0]));
                        rotate_motor2(distanceToSteps(m[1]));
                        rotate_motor3(distanceToSteps(m[2]));

                    }
                    break;
                case 'R':
                    // code pour le caractère 'R'
                    x = position[0] + 1;
                    y = position[1];
                    if(norm({x, y}) < RADIUS-P_LENGTH) {
                        position[0] = x;
                        auto m = computeMove({x,y});

                        rotate_motor1(distanceToSteps(m[0]));
                        rotate_motor2(distanceToSteps(m[1]));
                        rotate_motor3(distanceToSteps(m[2]));

                    }
                    break;
                case 'M':
                    // code pour le caractère 'M'
                    electromagnet = 1;
                    break;
                case 'W':
                    // code pour le caractère 'M'
                    electromagnet = 0;
                    break;
                case 'U':
                    // code pour le caractère 'U'
                    nSleepM1 = 0;
                    nSleepM2 = 0;
                    nSleepM3 = 0;

                    dirPinM1 = 1;
                    dirPinM2 = 1;
                    dirPinM3 = 1;
                    for(int i = 0; i < STEPS_PER_CENTIMETER; i++) {
                        stepPin = 1;
                        wait_us(2000);
                        stepPin = 0;
                        wait_us(2000);
                    }
                    break;
                case 'D':
                    // code pour le caractère 'D'
                    nSleepM1 = 0;
                    nSleepM2 = 0;
                    nSleepM3 = 0;
                    
                    dirPinM1 = 0;
                    dirPinM2 = 0;
                    dirPinM3 = 0;
                    for(int i = 0; i < STEPS_PER_CENTIMETER; i++) {
                        stepPin = 1;
                        wait_us(2000);
                        stepPin = 0;
                        wait_us(2000);
                    }
                    break;
                default:
                    // code pour un caractère inconnu
                    break;
            }
        }
    }
}
