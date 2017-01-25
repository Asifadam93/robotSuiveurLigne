#include "mbed.h"

//Déclaration des AnalogIn sur lequel nos photorésistances sont branchées
AnalogIn prDroiteCoin(A0);
AnalogIn prDroite(A1);
AnalogIn prCentre(A2);
AnalogIn prGauche(A3);
AnalogIn prGaucheCoin(A4);

//Valeurs qui seront utilisées pour stockées les valeurs de nos photorésistances sur un sol "blanc"
float droiteCoinBlanc;
float droiteBlanc;
float centreBlanc;
float gaucheBlanc;
float gaucheCoinBlanc;

//Valeurs qui seront utilisées pour stockées les valeurs de nos photorésistances sur un sol "noir"
float droiteCoinNoire;
float droiteNoire;
float centreNoire;
float gaucheNoire;
float gaucheCoinNoire;


//valeur de seuil. Ces seront calculées à partir des valeurs Blanches et Noires
float droiteCoinSeuil;
float droiteSeuil;
float centreSeuil;
float gaucheSeuil;
float gaucheCoinSeuil;

//permet de savoir si on consière que la photorésistance du coin droit est sur un sol noir ou pas
bool isSensorCoinDroiteBlack() {
    if (prDroiteCoin.read() > droiteCoinSeuil){
        return true;
    } else {
        return false;
    }
} 
bool isSensorDroiteBlack() {
    if (prDroite.read() > droiteSeuil){
        return true;
    } else {
        return false;
    }
}  
bool isSensorCentreBlack() {
    if (prCentre.read() > centreSeuil){
        return true;
    } else {
        return false;
    }
}   

bool isSensorGaucheBlack() {
    if (prGauche.read() > gaucheSeuil){
        return true;
    } else {
        return false;
    }
}  
bool isSensorCoinGaucheBlack() {
    if (prGaucheCoin.read() > gaucheCoinSeuil){
        return true;
    } else {
        return false;
    }
} 
