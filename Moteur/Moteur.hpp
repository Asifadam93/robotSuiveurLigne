#ifndef _MOTEUR_HPP_
#define _MOTEUR_HPP_

#include "mbed.h"

class Moteur{
    
    private:
    DigitalOut  M1;
    DigitalOut  M2;
    PwmOut      E1;
    PwmOut      E2;
    float       tempoE;
    float       deltaE;
    Serial serialOut;
    
    const static float vitesseReference = 1.0f;
    const static float vitesseMax = 1.0f;
    
    public:
    Moteur();
    void avancer(int force);
    void stop();
    void tournerGauche(int force);
    void tournerDroite(int force);
    
};

#endif
