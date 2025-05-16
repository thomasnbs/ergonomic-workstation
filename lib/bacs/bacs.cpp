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

void presenceMain()
{

}