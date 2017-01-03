#include "mbed.h"

//Photorésistance init
AnalogIn prDroiteCoin(A0);
AnalogIn prDroite(A1);
AnalogIn prCentre(A2);
AnalogIn prGauche(A3);
AnalogIn prGaucheCoin(A4);

//Led init
DigitalOut  ledDroite(D13);

//Moteur init
DigitalOut  M1(D4);
PwmOut      E1(D5);
PwmOut      E2(D6);
DigitalOut  M2(D7);

// serial init
Serial pc(SERIAL_TX, SERIAL_RX);

void avancer(){
    M1 = false;
    E1 = 0.5f;
    M2 = false;
    E2 = 0.5f;
}


void stop(){
     E1 = 0.0f;
     E2 = 0.0f;
}

int main() {
    
    while(1) {
        pc.printf("GaucheCoin : %f, Gauche : %f, Centre : %f, Droite : %f, DroiteCoin : %f\n\r",
        prGaucheCoin.read(),prGauche.read(), prCentre.read(), prDroite.read(),prDroiteCoin.read());
        wait(1);
    }
}
