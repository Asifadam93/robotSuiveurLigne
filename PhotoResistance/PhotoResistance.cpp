#include "PhotoResistance.hpp"

PhotoResistance::PhotoResistance(): prDroiteCoin(A0), prDroite(A1), prCentre(A2), prGauche(A3), prGaucheCoin(A4), serialOut(SERIAL_TX, SERIAL_RX){
    // constructeur
    droiteCoinSeuil = 0.0f;
    droiteSeuil     = 0.0f;
    centreSeuil     = 0.0f;
    gaucheSeuil     = 0.0f;
    gaucheCoinSeuil = 0.0f;
    
    droiteCoinBlanc = 0.0f;
    droiteBlanc     = 0.0f;
    centreBlanc     = 0.0f;
    gaucheBlanc     = 0.0f;
    gaucheCoinBlanc = 0.0f;
    
    droiteCoinNoire = 0.0f;
    droiteNoire     = 0.0f;
    centreNoire     = 0.0f;
    gaucheNoire     = 0.0f;
    gaucheCoinNoire = 0.0f;
}

void PhotoResistance::capteurInit(){
    
    Led myLed;
    
    myLed.doK2000Light();
    wait(1);
    setWhileValues();
    
    myLed.doK2000Light();
    wait(1);
    setBlackValues();
    
    wait(1);
    setSeuilValues();
    myLed.doK2000Light();
    myLed.turnOnAllLed();
    wait(1);
    
}

void PhotoResistance::setWhileValues(){
    droiteCoinBlanc = prDroiteCoin.read();
    droiteBlanc     = prDroite.read();
    centreBlanc     = prCentre.read();
    gaucheBlanc     = prGauche.read();
    gaucheCoinBlanc = prGaucheCoin.read();
    
    serialOut.printf("Pr blanc \n\r DroiteC : %f, Droite : %f, Centre : %f Gauche : %f, GaucheC : %f \n\r",
        droiteCoinBlanc, droiteBlanc, centreBlanc, gaucheBlanc, gaucheCoinBlanc);
}

void PhotoResistance::setBlackValues(){
    droiteCoinNoire = prDroiteCoin.read();
    droiteNoire     = prDroite.read();
    centreNoire     = prCentre.read();
    gaucheNoire     = prGauche.read();
    gaucheCoinNoire = prGaucheCoin.read();
    
    serialOut.printf("Pr Noire \n\r DroiteC : %f, Droite : %f, Centre : %f Gauche : %f, GaucheC : %f \n\r",
        droiteCoinNoire, droiteNoire, centreNoire, gaucheNoire, gaucheCoinNoire);
}

void PhotoResistance::setSeuilValues(){
    droiteCoinSeuil = (((droiteCoinNoire - droiteCoinBlanc) * valSeuil) + droiteCoinBlanc);
    droiteSeuil     = (((droiteNoire - droiteBlanc) * valSeuil) + droiteBlanc);
    centreSeuil     = (((centreNoire - centreBlanc) * valSeuil) + centreBlanc);
    gaucheSeuil     = (((gaucheNoire - gaucheBlanc) * valSeuil) + gaucheBlanc);
    gaucheCoinSeuil = (((gaucheCoinNoire - gaucheCoinBlanc) * valSeuil) + gaucheCoinBlanc);
    
    serialOut.printf("Pr Seuil \n\r DroiteC : %f, Droite : %f, Centre : %f Gauche : %f, GaucheC : %f \n\r",
        droiteCoinSeuil, droiteSeuil, centreSeuil, gaucheSeuil, gaucheCoinSeuil);
}

bool PhotoResistance::isSensorDroiteCoinBlack(){
    return (prDroiteCoin.read() > droiteCoinSeuil) ? true:false;   
}

bool PhotoResistance::isSensorDroiteBlack(){
    return (prDroite.read() > droiteSeuil) ? true:false;   
}

bool PhotoResistance::isSensorCentreBlack(){
    return (prCentre.read() > centreSeuil) ? true:false;   
}

bool PhotoResistance::isSensorGaucheBlack(){
    return (prGauche.read() > gaucheSeuil) ? true:false; 
}

bool PhotoResistance::isSensorGaucheCoinBlack(){
    return (prGaucheCoin.read() > gaucheCoinSeuil) ? true:false;   
}

void PhotoResistance::getSensorsState(){
    if(isSensorGaucheCoinBlack()){
            serialOut.printf(" | ");    
        } else {
            serialOut.printf(" . "); 
        }
        
        if(isSensorGaucheBlack()){
            serialOut.printf(" | ");    
        } else {
            serialOut.printf(" . "); 
        }
        
        if(isSensorCentreBlack()){
            serialOut.printf(" | ");    
        } else {
            serialOut.printf(" . "); 
        }
        
        if(isSensorDroiteBlack()){
            serialOut.printf(" | ");    
        } else {
            serialOut.printf(" . "); 
        }
        
        if(isSensorDroiteCoinBlack()){
            serialOut.printf(" | ");    
        } else {
            serialOut.printf(" . "); 
        }
        
        serialOut.printf("\n\r");     
}