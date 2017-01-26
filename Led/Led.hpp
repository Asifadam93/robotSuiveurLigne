#ifndef _LED_HPP_
#define _LED_HPP_

#include "mbed.h"

class Led{
    
    private:
    DigitalOut  ledDroiteCoin;
    DigitalOut  ledDroite;
    DigitalOut  ledGauche;
    DigitalOut  ledGaucheCoin;
    
    DigitalIn   blueButton;
    
    public:
    Led();
    void turnOnAllLed();
    void turnOffAllLed();
    void doK2000Light();
    
};

#endif
