#include "mbed.h"

static float valSeuil = 0.3f;
//boolean informations spécifique sur le parcours
bool prioriteADroite    = false;
bool raccourci          = false;

//bouton utilisateur
DigitalIn mybutton(USER_BUTTON);

//Photorésistance init
AnalogIn prDroiteCoin(A0);
AnalogIn prDroite(A1);
AnalogIn prCentre(A2);
AnalogIn prGauche(A3);
AnalogIn prGaucheCoin(A4);

//Infrarouge sensor
DigitalIn irDroite(D4); 
DigitalIn irCentre(D3);
DigitalIn irGauche(D2);

//utilisé pour la lecture des sensorPR
float droiteCoin;
float droite;
float centre;
float gauche;
float gaucheCoin;

//init valeur blanche
float droiteCoinBlanc;
float droiteBlanc;
float centreBlanc;
float gaucheBlanc;
float gaucheCoinBlanc;

//init valeur noire
float droiteCoinNoire;
float droiteNoire;
float centreNoire;
float gaucheNoire;
float gaucheCoinNoire;


//valeur de seuil (passage du blanc au noir)
float droiteCoinSeuil;
float droiteSeuil;
float centreSeuil;
float gaucheSeuil;
float gaucheCoinSeuil;

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


void tournerGaucheViolent(){
    M1 = true;
    E1 = 1.0f;
    M2 = true;
    E2 = 0.2;
}
void tournerGauche(){
    M1 = true;
    E1 = 0.8f;
    M2 = true;
    E2 = 0.4f;
}
void avancer(){
    M1 = true;
    E1 = 1.0f;
    M2 = true;
    E2 = 1.0f;
}
void tournerDroite(){
    M1 = true;
    E1 = 0.4f;
    M2 = true;
    E2 = 0.8f;
}
void tournerDroiteViolent(){
    M1 = true;
    E1 = 0.2f;
    M2 = true;
    E2 = 1.0f;
}


void stop(){
     E1 = 0.0f;
     E2 = 0.0f;
}

void turnOnAllLed(){
    ledDroiteCoin   = true;
    ledDroite       = true;
    ledGauche       = true;
    ledGaucheCoin   = true;
}
void turnOffAllLed(){
    ledDroiteCoin   = false;
    ledDroite       = false;
    ledGauche       = false;
    ledGaucheCoin   = false;
}


void doK2000Light(){
    int a = 0;
    while(1) {
        for (a=1; a < 7; a++){
            if (mybutton == 0)
                return; 
            switch(a) {
                case 1: turnOffAllLed();
                        ledDroiteCoin   = true;
                        wait(0.07);
                        break;
                case 2: turnOffAllLed();
                        ledDroite   = true;
                        wait(0.07);
                        break;
                case 3: turnOffAllLed();
                        ledGauche   = true;
                        wait(0.07);
                        break;
                case 4: turnOffAllLed();
                        ledGaucheCoin   = true;
                        wait(0.07);
                        break;
                case 5: turnOffAllLed();
                        ledGauche   = true;
                        wait(0.07);
                        break;
                case 6: turnOffAllLed();
                        ledDroite   = true;
                        wait(0.07);
                        break;
            }
            
        }
    }
}

bool isSensorCoinDroiteBlack() {
    if (prDroiteCoin.read() > droiteCoinSeuil){
        return true;
    } else {
        return false;
    }
} 
bool isSensorDroiteBlack() {
    if (prDroite.read() > droiteSeuil){
        return true;
    } else {
        return false;
    }
}  
bool isSensorCentreBlack() {
    if (prCentre.read() > centreSeuil){
        return true;
    } else {
        return false;
    }
}   

bool isSensorGaucheBlack() {
    if (prGauche.read() > gaucheSeuil){
        return true;
    } else {
        return false;
    }
}  
bool isSensorCoinGaucheBlack() {
    if (prGaucheCoin.read() > gaucheCoinSeuil){
        return true;
    } else {
        return false;
    }
} 

//etalonnage (voir orthographe)
void initialisation() {
    doK2000Light();
    
    turnOnAllLed();
    wait(1);
    
    droiteCoinBlanc = prDroiteCoin.read();
    droiteBlanc     = prDroite.read();
    centreBlanc     = prCentre.read();
    gaucheBlanc     = prGauche.read();
    gaucheCoinBlanc = prGaucheCoin.read();
    
    
    doK2000Light();
    
    turnOnAllLed();
    wait(1);
    
    droiteCoinNoire = prDroiteCoin.read();
    droiteNoire     = prDroite.read();
    centreNoire     = prCentre.read();
    gaucheNoire     = prGauche.read();
    gaucheCoinNoire = prGaucheCoin.read();
    
    droiteCoinSeuil = (((droiteCoinNoire - droiteCoinBlanc) * valSeuil) + droiteCoinBlanc);
    droiteSeuil     = (((droiteNoire - droiteBlanc) * valSeuil) + droiteBlanc);
    centreSeuil     = (((centreNoire - centreBlanc) * valSeuil) + centreBlanc);
    gaucheSeuil     = (((gaucheNoire - gaucheBlanc) * valSeuil) + gaucheBlanc);
    gaucheCoinSeuil = (((gaucheCoinNoire - gaucheCoinBlanc) * valSeuil) + gaucheCoinBlanc);
    
    
    pc.printf("Blanc \n\r DroiteC : %f, Droite : %f, Centre : %f Gauche : %f, GaucheC : %f \n\r",
        droiteCoinBlanc, droiteBlanc, centreBlanc, gaucheBlanc, gaucheCoinBlanc);
    
    pc.printf("Noire \n\r DroiteC : %f, Droite : %f, Centre : %f Gauche : %f, GaucheC : %f \n\r",
        droiteCoinNoire, droiteNoire, centreNoire, gaucheNoire, gaucheCoinNoire);
        
    pc.printf("Seuil \n\r DroiteC : %f, Droite : %f, Centre : %f Gauche : %f, GaucheC : %f \n\r",
        droiteCoinSeuil, droiteSeuil, centreSeuil, gaucheSeuil, gaucheCoinSeuil);
       
}
int main() {
    
    initialisation();
    doK2000Light();
    turnOnAllLed();
    wait(1);
    
    
    while(1) {
        
        
       
        if((irDroite == 0) || ( irCentre == 0)){
            stop();
        } else if ((isSensorCentreBlack() && !isSensorDroiteBlack() && !isSensorGaucheBlack()) ||
            (isSensorCentreBlack() && isSensorDroiteBlack() && isSensorGaucheBlack())) { 
            avancer();   
        } else if(isSensorCoinDroiteBlack()) {
          tournerGaucheViolent();
        } else if(isSensorCoinGaucheBlack()) {
            tournerDroiteViolent();     
        } else if (isSensorDroiteBlack()) {
            tournerGauche();
        } else if (isSensorGaucheBlack()) {
            tournerDroite();

        } else {
            stop();    
        }
    }
}
