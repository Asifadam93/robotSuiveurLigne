#include "InfraRouge.hpp"

InfraRouge::InfraRouge(): irDroite(D4), irCentre(D3), irGauche(D2){
    // constructeur
}

bool InfraRouge::isDroiteDetected(){
    return irDroite ? true:false;
}

bool InfraRouge::isCentreDetected(){
    return irCentre ? true:false;
}
    
bool InfraRouge::isGaucheDetected(){
    return irGauche ? true:false;
}