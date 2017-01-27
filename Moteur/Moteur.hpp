#ifndef _MOTEUR_HPP_
#define _MOTEUR_HPP_

#include "mbed.h"

class Moteur{
    
    private:
    DigitalOut  M1;
    DigitalOut  M2;
    PwmOut      E1;
    PwmOut      E2;
    
    const static float vitesseMax = 1.0f;
    const static float vitesseNormal = 0.5f;
    
    public:
    Moteur();
    void avancer();
    void stop();
    void tournerGauche();
    void tournerGaucheViolent();
    void tournerDroite();
    void tournerDroiteViolent();
    
};

#endif