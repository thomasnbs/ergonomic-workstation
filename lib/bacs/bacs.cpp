#include <Arduino.h>
#include "bacs.h"
#include <Wire.h>


void commanderLedsbac(uint8_t numeroDuBac, byte etat)
{
    numeroDuBac --;
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


/*void bacSelectionne(uint8_t numeroDuBac)
{
    Wire.beginTransmission(ADRESSE_BASE_BACS + numeroDuBac);
    Wire.write(ALLUMER_LED_VERTE);
    Wire.endTransmission();
}
*/

/*void presenceMain(uint8_t octetDuBac, byte capteurValeur)
{
    byte valeur = octetDuBac & CAPTEUR_DE_PRESENCE;
    Wire.beginTransmission(octetDuBac + CAPTEUR_DE_PRESENCE);
    Wire.write(capteurValeur);
    Wire.endTransmission();
}
*/