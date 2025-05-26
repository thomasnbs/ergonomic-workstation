#include <Arduino.h>
#include "bacs.h"
#include <Wire.h>


void commanderLedsBac(uint8_t numeroDuBac, byte etat)
{
    
}

bool etatBoutonValider()
{
    static bool etatPrecedent = RELACHE;
    bool etatActuel = digitalRead(BOUTON_VALIDER);

    if (etatActuel == APPUYER && etatPrecedent == RELACHE)
    {
        etatPrecedent = APPUYER;
        return true; // Le bouton a été pressé
    }
    else if (etatActuel == RELACHE && etatPrecedent == APPUYER)
    {
        etatPrecedent = RELACHE;
        return false; // Le bouton a été relâché
    }
    return false; // Aucun changement d'état
}

void bacSelectionne(uint8_t numeroDuBac)
{
    Wire.beginTransmission(ADRESSE_BASE_BACS + numeroDuBac);
    Wire.write(ALLUMER_LED_VERTE);
    Wire.endTransmission();
}


/* void presenceMain(uint8_t octetDuBac)
{
    byte reponseI2C;

    
    
    //Serial.print(octetDuBac, BIN);
    //uint8_t CAPTEUR_DE_PRESENCE = ADRESSE_BASE_BACS.digitalRead();
}*/


/*void buzzer()
*/