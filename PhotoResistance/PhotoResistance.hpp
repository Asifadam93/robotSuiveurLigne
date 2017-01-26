#ifndef _PHOTORESISTANCE_HPP_
#define _PHOTORESISTANCE_HPP_

#include "mbed.h"
#include "Led.hpp"

class PhotoResistance{
    
    private:
    const static float valSeuil = 0.3f;
    
    void setWhileValues();
    void setBlackValues();
    void setSeuilValues();
    
    AnalogIn prDroiteCoin;
    AnalogIn prDroite;
    AnalogIn prCentre;
    AnalogIn prGauche;
    AnalogIn prGaucheCoin;
    
    //valeur de seuil (passage du blanc au noir)
    float droiteCoinSeuil;
    float droiteSeuil;
    float centreSeuil;
    float gaucheSeuil;
    float gaucheCoinSeuil;
    
    //valeur blanc
    float droiteCoinBlanc;
    float droiteBlanc;
    float centreBlanc;
    float gaucheBlanc;
    float gaucheCoinBlanc;
    
    //valeur noire
    float droiteCoinNoire;
    float droiteNoire;
    float centreNoire;
    float gaucheNoire;
    float gaucheCoinNoire;
    
    public:
    PhotoResistance();
    void capteurInit();
    bool isSensorDroiteCoinBlack();
    bool isSensorDroiteBlack();
    bool isSensorCentreBlack();
    bool isSensorGaucheBlack();
    bool isSensorGaucheCoinBlack();
    
};

#endif