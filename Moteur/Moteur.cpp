#include "Moteur.hpp"

Moteur::Moteur(): M1(D8), M2(D7), E1(D9), E2(D6){
    // constructeur
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
    if (force == 0) {
        M2 = false;
        E2 = vitesseReference/2;
        M1 = true;
        E1 = vitesseReference/2;
        return;
    }
    M1 = true;
    E1 = vitesseReference;
    
    if ((force >= 1) && (force <=4)) {
        M2 = true;
        E2 = vitesseReference - ((vitesseReference/float(4)) * float(force));
    }
    if (force >=4 ) {
        E1 = vitesseMax;
    }
    if (force == 5) {
        M2 = false;
        E2 = vitesseReference /float(2);
    }

}

void Moteur::tournerDroite(int force){
    if (force == 0) {
        M2 = true;
        E2 = vitesseReference/2;
        M1 = false;
        E1 = vitesseReference/2;
        return;
    }
    M2 = true;
    E2 = vitesseReference;
    
    if ((force >= 1) && (force <=4)) {
        M1 = true;
        E1 = vitesseReference - ((vitesseReference/float(4)) * float(force));
    }
    if (force >=4 ) {
        E2 = vitesseMax;
    }
    if (force >= 5) {
        M1 = false;
        E1 = vitesseReference /float(2);
    }

}


