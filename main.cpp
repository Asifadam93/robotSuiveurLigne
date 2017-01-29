#include "mbed.h"
#include <time.h>
#include "PhotoResistance.hpp"
#include "Led.hpp"
#include "Moteur.hpp"

//boolean informations spécifique sur le parcours
bool prioriteADroite    = false;
bool raccourci          = false;

//mémorisation des capteurs
bool cg, g, c, d, cd;

//timer
clock_t timerSortie;

//temps d'attente
double tempsAttenteSortie;

//permet de mémoriser la dernière direction prise par le robot
char lastDir = ' ';

//instanciation des objets
PhotoResistance myPR;
Led myLed;
Moteur myMoteur;
Serial serialOut(SERIAL_TX, SERIAL_RX);
DigitalIn blueButton(USER_BUTTON);

void refreshCapteur() {
    /**
     * Mémorisation  des capteurs
     */
     cg = myPR.isSensorGaucheCoinBlack(); 
     g  = myPR.isSensorGaucheBlack(); 
     c  = myPR.isSensorCentreBlack(); 
     d  = myPR.isSensorDroiteBlack(); 
     cd = myPR.isSensorDroiteCoinBlack(); 
}

int main() {
    
    myPR.capteurInit();
    myLed.turnOnAllLed();
    wait(1);
    
     while(1) {
        refreshCapteur();
        /**
         *  Déplacement
         */  
        if  ((!g && c && !d) || (g && c && d)) {
            myMoteur.avancer();
            lastDir = 'e';
        } else if( cd ) {
            myMoteur.tournerGaucheViolent();
            lastDir = 'a';
        } else if( cg ) {
            myMoteur.tournerDroiteViolent();  
            lastDir = 't';
        } else if ( d ) {
            myMoteur.tournerGauche();
            lastDir = 'z';
        } else if ( g ) {
            myMoteur.tournerDroite();
            lastDir = 'r';
        //fonctionnement sortie ou fin du parcours
        } else {
            myMoteur.stop();
            if ( (lastDir == 'a') || (lastDir == 'z') ) {
                timerSortie = clock();
                tempsAttenteSortie = clock() - timerSortie;
                
                while((tempsAttenteSortie < 50) && (!c)) {
                    myMoteur.tournerGaucheExtreme();
                    tempsAttenteSortie = clock() - timerSortie;
                    refreshCapteur(); 
                }
                lastDir = ' ';
                
                
            } else if ( (lastDir == 't') || (lastDir == 'r') ) {
                timerSortie = clock();
                tempsAttenteSortie = clock() - timerSortie;
                
                while((tempsAttenteSortie < 50) && (!c)) {
                    myMoteur.tournerDroiteExtreme();
                    tempsAttenteSortie = clock() - timerSortie;
                    refreshCapteur();
                }
                lastDir = ' ';
            } else {
                myMoteur.stop();
                while(!(blueButton == 0)) {
                    serialOut.printf("%d - %d - %d - %d - %d * lastDir : %c tempsAttenteSortie : %f\n\r", cg, g, c, d, cd, lastDir, tempsAttenteSortie);
                    wait(1);
                }
                
            } 
        }
        
        
        /**
         *
        */
    }
    
}
