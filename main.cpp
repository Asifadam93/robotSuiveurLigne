#include "mbed.h"
#include "PhotoResistance.hpp"
#include "InfraRouge.hpp"
#include <time.h>

InfraRouge myIR;
PhotoResistance myPr;
Serial serialOut(SERIAL_TX, SERIAL_RX);

//boolean informations spécifique sur le parcours
bool prioriteADroite    = false;
bool raccourci          = false;

//timer
clock_t timer1;
clock_t timer2;

//temps d'attente
double timeAttente1;
double timeAttente2;

int main() {
    
    myPr.capteurInit();
    
    while(1){
        
        myPr.getSensorsState();
        
    }
    
    /*timer1 = clock();
    timer2 = clock();
    
    while(1){
        
        //détection priorité à droite
        if (!myPr.isSensorCoinGaucheBlack() && !myPr.isSensorGaucheBlack() && myPr.isSensorCentreBlack() && myPr.isSensorDroiteBlack() && myPr.isSensorCoinDroiteBlack()){
            prioriteADroite = true;
            timer1          = clock();
        } else if(isSensorCoinGaucheBlack() && isSensorGaucheBlack() && isSensorCentreBlack() && !isSensorDroiteBlack() && !isSensorCoinDroiteBlack()){
                
        }   
    }*/
}
