#include <Arduino.h>
#include "bacs.h"
#include <Wire.h>


void commanderLedsBac(uint8_t numeroDuBac, byte etat)
{
    Wire.beginTransmission(ADRESSE_BASE_BACS + numeroDuBac);
    Wire.write(etat);
    Wire.endTransmission();
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


void presenceMain(uint8_t octetDuBac)
{
    
}


/*void buzzer()
*/