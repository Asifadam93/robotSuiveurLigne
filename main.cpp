#include "mbed.h"
#include <time.h>
#include "PhotoResistance.hpp"
#include "Led.hpp"
#include "Moteur.hpp"
#include "InfraRouge.hpp"

//boolean informations spécifique sur le parcours
bool suspicionPrioriteADroite   = false;
bool prioriteADroite            = false;
bool suspicionRaccourci         = false;
bool raccourci                  = false;
bool virageEnCours              = false;

//mémorisation des capteurs
bool cg, g, c, d, cd;
bool cgOld, gOld, cOld, dOld, cdOld;

//timer
clock_t timerSortie = clock();
clock_t timerPrioriteOuRaccourci = clock();
clock_t timerVirage = clock();

//temps d'attente
double tempsAttenteSortie = 0;
double tempsAttenteVirage = 0;
double tempsAttentePrioriteOuRaccourci = 0;

//permet de mémoriser la dernière direction prise par le robot
int lastDir = ' ';

//instanciation des objets
PhotoResistance myPR;
Led myLed;
InfraRouge myIR;
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

        
        /**
         *  Déplacement
         */  
        if ((myIR.isDroiteDetected() || myIR.isCentreDetected())) {
             while(myIR.isDroiteDetected() || myIR.isCentreDetected()|| myIR.isGaucheDetected() ) {
                myMoteur.stop();
                wait(1);
             }
        } else if (raccourci && (c && g && cg && !cd)) {
            myMoteur.stop();
            wait(5);
        } else if  ((!g && c && !d) || (g && c && d)) {
            myMoteur.avancer(2);
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
                        myMoteur.tournerGauche(5);
                    } else {
                        myMoteur.tournerGauche(6);
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
                        myMoteur.tournerDroite(5);
                    } else {
                        myMoteur.tournerDroite(6);
                    }
                    tempsAttenteSortie = clock() - timerSortie;
                    refreshCapteur();
                }
                
                lastDir = ' ';

            } else {
                myMoteur.stop();
 
            } 
        }

    }
    
}
