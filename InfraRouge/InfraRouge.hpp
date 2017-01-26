#ifndef _INFRAROUGE_HPP_
#define _INFRAROUGE_HPP_

#include "mbed.h"

class InfraRouge{
    
    private:
    DigitalIn irDroite; 
    DigitalIn irCentre;
    DigitalIn irGauche;
    
    public:
    InfraRouge();
    bool isDroiteDetected();
    bool isCentreDetected();
    bool isGaucheDetected();
    
};

#endif