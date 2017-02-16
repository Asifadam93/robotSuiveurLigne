#include "mbed.h"
#include <time.h>
#include "PhotoResistance.hpp"
#include "Led.hpp"
#include "Moteur.hpp"
#include "InfraRouge.hpp"

//boolean informations spécifique sur le parcours
bool suspicionPrioriteADroite   = false;
bool prioriteADroite            = false;
bool virageEnCours              = false;
bool raccourci                  = false;

//mémorisation des capteurs
bool cg, g, c, d, cd;
bool cgOld, gOld, cOld, dOld, cdOld;

//timer
clock_t timerSortie;
clock_t timerPriorite;
clock_t timerVirage;

//temps d'attente
double tempsAttenteSortie;
double tempsAttentePriorite;

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
         //TEST PRIORITE

        /**
          * Gestion de la détection des racourcis ou des priorités
          */
          //TODO AMELIORER DETECTION ET RALENTIR (si possible)
        tempsAttentePriorite = (clock() - timerPriorite);
        
         /*if (virageEnCours == true) {
            timerVirage  = (clock() - timerVirage);
            if (timerVirage > 5) {
                virageEnCours = false;
            } 
        }
        

        if (virageEnCours == false) {
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
        }
        */

        
        /**
         *  Déplacement
         */  
        
        if (/*prioriteADroite && */(myIR.isDroiteDetected() || myIR.isCentreDetected())) {
             while(myIR.isDroiteDetected() || myIR.isCentreDetected()|| myIR.isGaucheDetected() ) {
                myMoteur.stop();
                wait(1);
             }
        } else if ((!g && c && !d) || (g && c && d)) {
            myMoteur.avancer();
            lastDir = 5;
        } else if( cd && !d) {
            myMoteur.tournerGauche(4);
            virageEnCours=true;
            timerVirage = clock();
            lastDir = 1;
        } else if( cd && d) {
            myMoteur.tournerGauche(3);
            timerVirage = clock();
            virageEnCours=true;
            lastDir = 2;
        } else if( d && !c) {
            myMoteur.tournerGauche(2);
            timerVirage = clock();
            virageEnCours=true;
            lastDir = 3;
        } else if( d && c) {
            myMoteur.tournerGauche(1);
            lastDir = 4;
        } else if( cg && !g) {
            myMoteur.tournerDroite(4);
            timerVirage = clock();
            virageEnCours=true;
            lastDir = 9;
        } else if( cg && g) {
            myMoteur.tournerDroite(3);
            timerVirage = clock();
            virageEnCours=true;
            lastDir = 8;
        } else if( g && !c) {
            myMoteur.tournerDroite(2);
            timerVirage = clock();
            virageEnCours=true;
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
                        myMoteur.tournerGauche(6);
                    } else {
                        myMoteur.tournerGauche(7);
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
                        myMoteur.tournerDroite(6);
                    } else {
                        myMoteur.tournerDroite(7);
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
