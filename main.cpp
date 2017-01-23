#include "mbed.h"

//Photorésistance init
AnalogIn prDroiteCoin(A0);
AnalogIn prDroite(A1);
AnalogIn prCentre(A2);
AnalogIn prGauche(A3);
AnalogIn prGaucheCoin(A4);

float droiteCoin;
float droite;
float centre;
float gauche;
float gaucheCoin;

// IR object detector
DigitalIn irDroite(D4);
DigitalIn irCentre(D3);
DigitalIn irGauche(D2);

//Led init
DigitalOut  ledDroiteCoin(D13);
DigitalOut  ledDroite(D12);
DigitalOut  ledGauche(D11);
DigitalOut  ledGaucheCoin(D10);

//Moteur init
DigitalOut  M1(D8);
PwmOut      E1(D9);
PwmOut      E2(D6);
DigitalOut  M2(D7);

// serial init
Serial pc(SERIAL_TX, SERIAL_RX);

void avancer(){
    M1 = true;
    E1 = 0.5f;
    M2 = true;
    E2 = 0.5f;
}

/*id droite(){
    M1 = true;
    E1 = 0.5f;
    M2 = false;
    E2 = 0.5f;
}*/


void stop(){
     E1 = 0.0f;
     E2 = 0.0f;
}

void turnOnAllLed(){
    ledDroiteCoin = true;
    ledDroite = true;
    ledGauche = true;
    ledGaucheCoin = true;
}


int main() {
    
    turnOnAllLed();
    
    //avancer();
    
    while(1) {
        if ((irDroite == 1) && (irCentre == 1) && (irGauche == 1)) {
            pc.printf("Avancer\n\r");
            avancer();
        } else {
            pc.printf("Danger STOP ! !n\r");
            stop();
        }

        
        // read sensors values
        /*droiteCoin = prDroiteCoin.read();
        droite = prDroite.read();
        centre = prCentre.read();
        gauche = prGauche.read();
        gaucheCoin = prGaucheCoin.read();
        
        pc.printf("GaucheCoin : %f, Gauche : %f, Centre : %f, Droite : %f, DroiteCoin : %f\n\r",
        gaucheCoin,gauche, centre, droite,droiteCoin);*/
        
        //pc.printf("IR gauche %d, IR centre %d, IR droite %d\n\r",gauche, centre, droite); 
        
        /*if(irDroite != 0){
            pc.printf("IR droite\n\r");  
        }
        
        if(irCentre != 0){
            pc.printf("IR centre\n\r");  
        }
        
        if(irGauche != 0){
            pc.printf("IR gauche\n\r");  
        }*/

    }
}
