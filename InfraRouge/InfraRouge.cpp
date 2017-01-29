#include "InfraRouge.hpp"

InfraRouge::InfraRouge(): irDroite(D4), irCentre(D3), irGauche(D2){
    // constructeur
}

bool InfraRouge::isDroiteDetected(){
    return irDroite ? false:true;
}

bool InfraRouge::isCentreDetected(){
    return irCentre ? false:true;
}
    
bool InfraRouge::isGaucheDetected(){
    return irGauche ? false:true;
}
