#include <Arduino.h>
#include <Wire.h>
#include <String.h>
//#include "BluetoothSerial.h"
#include "transmettre.h"
#include "bacs.h"


//#define numeroDuBac_8 7 // adresse du dernièr bac
#define NOM_DE_LA_STATION "EWS_4.0"

void setup()
{
  
  Serial.begin(VITESSE_SERIE);
  Wire.begin();         //init le bus I2c
  
intialiserBluetooth(NOM_DE_LA_STATION);
while(!bluetoothConnecte())
{

  for(uint8_t i=0;i<NOMBRE_DE_BACS;i++){
    Wire.beginTransmission(ADRESSE_BASE_BACS+i); // Début de la transmission à l'adresse 0x20
    Wire.write(ALLUMER_LED_VERTE);        
    Wire.endTransmission();
  }
 
delay(1000);

for(uint8_t i=0;i<NOMBRE_DE_BACS;i++){
  Wire.beginTransmission(ADRESSE_BASE_BACS+i); // Début de la transmission à l'adresse 0x20
  Wire.write(ALLUMER_LED_ROUGE);        
  Wire.endTransmission();
  }
delay(1000);
}

for(uint8_t i=0;i<NOMBRE_DE_BACS;i++){
  Wire.beginTransmission(ADRESSE_BASE_BACS+i); // Début de la transmission à l'adresse 0x20
  Wire.write(ETEINDRE_LEDS);        
  Wire.endTransmission();
 }
}

///////////////////////////////////////////////////////////////////////
void loop()
{
  
}

  