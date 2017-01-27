#include "Led.hpp"

Led::Led(): ledDroiteCoin(D13), ledDroite(D12), ledGauche(D11), ledGaucheCoin(D10), blueButton(USER_BUTTON){
    // constructeur
}

void Led::turnOnAllLed(){
    ledDroiteCoin   = true;
    ledDroite       = true;
    ledGauche       = true;
    ledGaucheCoin   = true;
}

void Led::turnOffAllLed(){
    ledDroiteCoin   = false;
    ledDroite       = false;
    ledGauche       = false;
    ledGaucheCoin   = false;
}

void Led::doK2000Light(){
    
    while(1) {
        
        for (int a=1; a < 7; a++){ 
    
            if (blueButton == 0){
                // button pressed !
                    turnOnAllLed();
                    return;
                }
    
            turnOffAllLed();
    
            switch(a) {
                case 1: 
                    ledDroiteCoin   = true;
                    wait(0.1);
                    break;
                case 2: 
                    ledDroite       = true;
                    wait(0.1);
                    break;
                case 3: 
                    ledGauche       = true;
                    wait(0.1);
                    break;
                case 4: 
                    ledGaucheCoin   = true;
                    wait(0.1);
                    break;
                case 5: 
                    ledGauche       = true;
                    wait(0.1);
                    break;
                case 6: 
                    ledDroite       = true;
                    wait(0.1);
                    break;
            }
        }
    }   
}