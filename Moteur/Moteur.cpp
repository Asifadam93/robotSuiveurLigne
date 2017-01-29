#include "Moteur.hpp"

Moteur::Moteur(): M1(D8), M2(D7), E1(D9), E2(D6){
    // constructeur
}

void Moteur::avancer(){
    M1 = true;
    E1 = vitesseHight;
    M2 = true;
    E2 = vitesseHight;
}

void Moteur::stop(){
    E1 = 0.0f;
    E2 = 0.0f;
}

void Moteur::tournerGauche(){
    M1 = true;
    E1 = vitesseHight;
    M2 = true;
    E2 = vitesseMedium;
}

void Moteur::tournerGaucheViolent(){
    M1 = true;
    E1 = vitesseHight;
    M2 = true;
    E2 = 0.0f;
}

void Moteur::tournerDroite(){
    M1 = true;
    E1 = vitesseMedium;
    M2 = true;
    E2 = vitesseHight;
}

void Moteur::tournerDroiteViolent(){
    M1 = true;
    E1 = 0.0f;
    M2 = true;
    E2 = vitesseHight;
}

