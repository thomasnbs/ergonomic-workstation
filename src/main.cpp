#include <Arduino.h>
#include <Wire.h>
#include "BluetoothSerial.h"

#define VITESSE_BLUETOOTH 9600
BluetoothSerial ergonomicWorkstation;

#define adresseBaseDesBacs 0x20
#define numeroDuBac_1 0
#define numeroDuBac_8 7 // adresse du dernièr bac
#define capteurBac_1 2
#define etatCapteurBac_1
#define NOMBRE_D_OCTETS 1
#define MASQUE_DE_PRESENCE_DE_MAIN 0x04 // 0b00000100

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
  
/*for*/

  Wire.requestFrom(adresseBaseDesBacs + numeroDuBac_1, NOMBRE_D_OCTETS); // Demande de 1 octet à l'adresse 0x20
  if(Wire.available()>0) 
  {
    uint8_t octetDuBac = Wire.read();
    bool presenceMain = (octetDuBac & MASQUE_DE_PRESENCE_DE_MAIN) ; // Vérifie si le bit de présence de la main est à 0
    /*sockage dans tableau ou création d'un octet de présence*/
   
  }

  /*end for*/
  ergonomicWorkstation.println(presenceMain); // Affiche la valeur binaire du registre d'état du bac 1

}

