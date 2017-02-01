#include "mbed.h"
#include <time.h>
#include "PhotoResistance.hpp"
#include "Led.hpp"
#include "Moteur.hpp"
#include "InfraRouge.hpp"


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
int lastDir = 0;

//instanciation des objets
PhotoResistance myPR;
Led myLed;
Moteur myMoteur;
InfraRouge myIR;
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

        /**
          * Gestion de la détection des racourcis ou des priorités
          */
          //TODO AMELIORER DETECTION ET RALENTIR (si possible)
        tempsAttentePriorite = (clock() - timerPriorite);

        if (tempsAttentePriorite > 10) {
            suspicionPrioriteADroite = false;
        }
        if (tempsAttentePriorite > 20) {
            prioriteADroite = false;
        }
                    
        //gestion de la priorité  
        if ((cdOld  && !cd  ) &&
            (suspicionPrioriteADroite == true) && (tempsAttentePriorite < 10) ) {
            myLed.turnOffAllLed();
            wait(0.05);
            myLed.turnOnAllLed();
            
            prioriteADroite = true;
            suspicionPrioriteADroite = false;
        }
        if ((!cdOld  && cd && !prioriteADroite) && !(cd && d && c && g && cg) && (lastDir >3))  {

            suspicionPrioriteADroite = true;
            prioriteADroite          = false;
            timerPriorite = clock();
            tempsAttentePriorite = 0;
        }
        //FIN TEST PRIORITE
        
        
        /**
         *  Déplacement
         */  
        if (prioriteADroite && (myIR.isDroiteDetected() || myIR.isCentreDetected())) {
             while(myIR.isDroiteDetected() || myIR.isCentreDetected()|| myIR.isGaucheDetected() ) {
                myMoteur.stop();
                wait(1);
             }
        } else if  ((!g && c && !d) || (g && c && d)) {
            myMoteur.avancer();
            lastDir = 5;
        } else if( cd && !d) {
            myMoteur.tournerGauche(4);
            lastDir = 1;
        } else if( cd && d ) {
            myMoteur.tournerGauche(3);
            lastDir = 2;
        } else if( d && !c) {
            myMoteur.tournerGauche(2);
            lastDir = 3;
        } else if( d && c ) {
            myMoteur.tournerGauche(1);
            lastDir = 4;
        } else if( cg && !g) {
            myMoteur.tournerDroite(4);
            lastDir = 9;
        } else if( cg && g ) {
            myMoteur.tournerDroite(3);
            lastDir = 8;
        } else if( g && !c) {
            myMoteur.tournerDroite(2);
            lastDir = 7;
        } else if( g && c ) {
            myMoteur.tournerDroite(1);
            lastDir = 6;
        //fonctionnement sortie ou fin du parcours
        } else {
            if (( lastDir != 0 ) && (( lastDir > 3 ) && ( lastDir < 7 ))){

                //DEBUT CAUSE PROBLEME
                timerSortie = clock();
                tempsAttenteSortie = (double)(clock() - timerSortie);

                while((tempsAttenteSortie < 100) && !d) {
                    myMoteur.tournerGauche(0); // mef, tournerGauche(5) ne fait pas rester sur place : 1, -0.4, à voir si ca ne cause pas problème
                    tempsAttenteSortie = (double)(clock() - timerSortie);
                    refreshCapteur();
                }  
 
                while((tempsAttenteSortie < 270) && !g) {
                    myMoteur.tournerDroite(0);  // mef, tournerDroite(5) ne fait pas rester sur place : 1, -0.4, à voir si ca ne cause pas problème
                    tempsAttenteSortie = (double)(clock() - timerSortie);
                    refreshCapteur();
                }

                if ((tempsAttenteSortie >= 270) || d || g) {
                    lastDir = 0;
                    myMoteur.stop();
                    wait(2);
                }
                    
                //FIN CAUSE PROBLEME
            } else if (( lastDir <= 3 ) && (lastDir >0)) {
                timerSortie = clock();
                tempsAttenteSortie = (double)(clock() - timerSortie);
                
                while((tempsAttenteSortie < 60) && (!d)) {
                    if (tempsAttenteSortie <= 40) {
                        myMoteur.tournerGauche(4);
                    } else {
                        myMoteur.tournerGauche(5);
                    }
                    tempsAttenteSortie = (double)(clock() - timerSortie);
                    refreshCapteur(); 
                }
                if (tempsAttenteSortie >= 60)
                    lastDir = 0;
            } else if ( lastDir >= 7 ) {
                timerSortie = clock();
                tempsAttenteSortie = (double)(clock() - timerSortie);
                
                while((tempsAttenteSortie < 60) && (!g)) {
                    if (tempsAttenteSortie <= 40) {
                        myMoteur.tournerDroite(4);
                    } else {
                        myMoteur.tournerDroite(5);
                    }
                    tempsAttenteSortie = (double)(clock() - timerSortie);
                    refreshCapteur();
                }
                if (tempsAttenteSortie >= 60)
                    lastDir = 0;
            } else {
                myMoteur.stop();
                /**/
            } 
        }

    }
    
}

