#include <Arduino.h>
#include <Wire.h>

#define adresseBaseDesBacs 0x20
#define numeroDuBac_1 0
#define numeroDuBac_2 1
#define numeroDuBac_3 2

#define ATTENDRE_1_SECONDE 1000

void setup() {
 Wire.begin();


}

void loop() {
  Wire.beginTransmission(adresseBaseDesBacs + numeroDuBac_1); // Début de la transmission à l'adresse 0x20
  Wire.write(0b11111110);                             // 
  Wire.endTransmission();
  delay(ATTENDRE_1_SECONDE);
  Wire.beginTransmission(adresseBaseDesBacs + numeroDuBac_1); // Début de la transmission à l'adresse 0x20
  Wire.write(0b11111111);                             // 
  Wire.endTransmission();
  delay(ATTENDRE_1_SECONDE);

}
