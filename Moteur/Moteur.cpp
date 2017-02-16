#include "Moteur.hpp"
#include <cmath>

Moteur::Moteur(): M1(D8), M2(D7), E1(D9), E2(D6), serialOut(SERIAL_TX, SERIAL_RX){
    // constructeur
    deltaE  = ((vitesseReference * float(2)) /float(6));
}

void Moteur::avancer(){
    M1 = true;
    E1 = vitesseMax;
    M2 = true;
    E2 = vitesseMax;
}

void Moteur::stop(){
    E1 = 0.0f;
    E2 = 0.0f;
}

void Moteur::tournerGauche(int force){
    M1 = true;
    E1 = vitesseReference;
    M2 = true;
    tempoE = vitesseReference - (deltaE * float(force));
    
    if (tempoE <0.0f) {
        E2 = abs(tempoE);
        M2 = false;
    } else {
        E2 = tempoE;
    }
}

void Moteur::tournerDroite(int force){
    M2 = true;
    E2 = vitesseReference;
    M1 = true;
    tempoE = vitesseReference - (deltaE * float(force));
    
    if (tempoE <0.0f) {
        E1 = abs(tempoE);
        M1 = false;
    } else {
        E1 = tempoE;
    }
}

