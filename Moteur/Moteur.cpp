#include "Moteur.hpp"

Moteur::Moteur(): M1(D8), M2(D7), E1(D9), E2(D6){
    // constructeur
}

void Moteur::avancer(){
    M1 = true;
    E1 = vitesseNormal;
    M2 = true;
    E2 = vitesseNormal;
}

void Moteur::stop(){
    E1 = 0.0f;
    E2 = 0.0f;
}

void Moteur::tournerGauche(){
    M1 = true;
    E1 = 0.8f;
    M2 = true;
    E2 = 0.4f;
}

void Moteur::tournerGaucheViolent(){
    M1 = true;
    E1 = 1.0f;
    M2 = true;
    E2 = 0.2;
}

void Moteur::tournerDroite(){
    M1 = true;
    E1 = 0.4f;
    M2 = true;
    E2 = 0.8f;
}

void Moteur::tournerDroiteViolent(){
    M1 = true;
    E1 = 0.2f;
    M2 = true;
    E2 = 1.0f;
}
