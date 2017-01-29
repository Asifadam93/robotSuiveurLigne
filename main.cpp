#include "mbed.h"
#include <time.h>
#include "PhotoResistance.hpp"
#include "Led.hpp"
#include "Moteur.hpp"

//boolean informations spécifique sur le parcours
bool suspicionPrioriteADroite   = false;
bool prioriteADroite            = false;
bool raccourci                  = false;

//mémorisation des capteurs
bool cg, g, c, d, cd;
bool cgOld, gOld, cOld, dOld, cdOld;

//timer
clock_t timerSortie;
clock_t timerPriorite;

//temps d'attente
double tempsAttenteSortie;
double tempsAttentePriorite;

//permet de mémoriser la dernière direction prise par le robot
int lastDir = ' ';

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
     
     cgOld = cg; 
     gOld  = g; 
     cOld  = c;
     dOld  = d;
     cdOld = cd;
     
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
        
        //TEST PRIORITE
        tempsAttentePriorite = (clock() - timerPriorite);

        if (tempsAttentePriorite > 10) {
            prioriteADroite = false;
            suspicionPrioriteADroite = false;
        }
        /**
          * Gestion de la détection des racourcis ou des priorités
          */
        //gestion de la priorité  
        if ((cdOld  && !cd ) &&
            (suspicionPrioriteADroite == true) && (tempsAttentePriorite < 10) ) {
            myLed.turnOffAllLed();
            wait(0.05);
            myLed.turnOnAllLed();
            
            prioriteADroite = true;
            suspicionPrioriteADroite = false;
        }
        if (!cdOld  && cd ) {

            suspicionPrioriteADroite = true;
            prioriteADroite          = false;
            timerPriorite = clock();
            tempsAttentePriorite = 0;
        }
        //FIN TEST PRIORITE
        
        
        /**
         *  Déplacement
         */  
        if  ((!g && c && !d) || (g && c && d)) {
            myMoteur.avancer();
            lastDir = 5;
        } else if( cd && !d) {
            myMoteur.tournerGauche(4);
            lastDir = 1;
        } else if( cd && d) {
            myMoteur.tournerGauche(3);
            lastDir = 2;
        } else if( d && !c) {
            myMoteur.tournerGauche(2);
            lastDir = 3;
        } else if( d && c) {
            myMoteur.tournerGauche(1);
            lastDir = 4;
        } else if( cg && !g) {
            myMoteur.tournerDroite(4);
            lastDir = 9;
        } else if( cg && g) {
            myMoteur.tournerDroite(3);
            lastDir = 8;
        } else if( g && !c) {
            myMoteur.tournerDroite(2);
            lastDir = 7;
        } else if( g && c) {
            myMoteur.tournerDroite(1);
            lastDir = 6;
        //fonctionnement sortie ou fin du parcours
        } else {
            if ( (lastDir == 1) || (lastDir == 2) ) {
                timerSortie = clock();
                tempsAttenteSortie = clock() - timerSortie;
                
                while((tempsAttenteSortie < 60) && (!d)) {
                    if (tempsAttenteSortie <= 20) {
                        myMoteur.tournerGauche(4);
                    } else {
                        myMoteur.tournerGauche(5);
                    }
                    tempsAttenteSortie = clock() - timerSortie;
                    refreshCapteur(); 
                }
                lastDir = ' ';

            } else if ( (lastDir == 8) || (lastDir == 9) ) {
                timerSortie = clock();
                tempsAttenteSortie = clock() - timerSortie;
                
                while((tempsAttenteSortie < 60) && (!g)) {
                    if (tempsAttenteSortie <= 20) {
                        myMoteur.tournerDroite(4);
                    } else {
                        myMoteur.tournerDroite(5);
                    }
                    tempsAttenteSortie = clock() - timerSortie;
                    refreshCapteur();
                }
                
                lastDir = ' ';

            } else {
                myMoteur.stop();
                /*while(!(blueButton == 0)) {
                    serialOut.printf("%d - %d - %d - %d - %d * lastDir : %c tempsAttenteSortie : %f\n\r", cg, g, c, d, cd, lastDir, tempsAttenteSortie);
                    wait(1);
                }*/
            } 
        }

    }
    
}

