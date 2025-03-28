#include <Arduino.h>
#include <Wire.h>
#include "BluetoothSerial.h"

#define VITESSE_BLUETOOTH 9600
BluetoothSerial ergonomicWorkstation;

#define adresseBaseDesBacs 0x20
#define numeroDuBac_1 0
#define numeroDuBac_2 1
#define numeroDuBac_3 
#define capteurBac_1 2
#define etatCapteurBac_1

#define ATTENDRE_1_SECONDE 1000


void setup() {
 Wire.begin();
 ergonomicWorkstation.begin("EWS_4.0"); //adresse MAC = 08:3A:F2:AA:74:06
 Serial.begin(VITESSE_BLUETOOTH);


}

void loop() {
  Wire.beginTransmission(adresseBaseDesBacs + numeroDuBac_1); // Début de la transmission à l'adresse 0x20
  Wire.write(0b11111101);                             // 
  Wire.endTransmission();
  delay(ATTENDRE_1_SECONDE);
  Wire.beginTransmission(adresseBaseDesBacs + numeroDuBac_1); // Début de la transmission à l'adresse 0x20
  Wire.write(0b11111110);                             // 
  Wire.endTransmission();
  delay(ATTENDRE_1_SECONDE);
  ergonomicWorkstation.println(adresseBaseDesBacs,BIN);
}

