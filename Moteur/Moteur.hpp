#ifndef _MOTEUR_HPP_
#define _MOTEUR_HPP_

#include "mbed.h"

class Moteur{
    
    private:
    DigitalOut  M1;
    DigitalOut  M2;
    PwmOut      E1;
    PwmOut      E2;
    
    const static float vitesseHight     = 0.8f;
    const static float vitesseMedium    = 0.6f;
    const static float vitesseNormal    = 0.4f;
    
    public:
    Moteur();
    void avancer();
    void stop();
    void tournerGauche();
    void tournerGaucheViolent();
    void tournerGaucheExtreme();
    void tournerDroite();
    void tournerDroiteViolent();
    void tournerDroiteExtreme();
    
};

#endif

