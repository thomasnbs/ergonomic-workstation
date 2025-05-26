#include <Arduino.h>
#include <Wire.h>
#include "transmettre.h"
#include "bacs.h"
//#include "affichage.h"

#define NOM_DE_LA_STATION "EWS_4.0"

void setup()
{
  Serial.begin(VITESSE_SERIE);
  Wire.begin();

  intialiserBluetooth(NOM_DE_LA_STATION);

  while (!bluetoothConnecte())
  {
    for (uint8_t i = 0; i < NOMBRE_DE_BACS; i++)
    {
      Wire.beginTransmission(ADRESSE_BASE_BACS + i);
      Wire.write(ALLUMER_LED_VERTE);
      Wire.endTransmission();
    }
    delay(1000);

    for (uint8_t i = 0; i < NOMBRE_DE_BACS; i++)
    {
      Wire.beginTransmission(ADRESSE_BASE_BACS + i);
      Wire.write(ALLUMER_LED_ROUGE);
      Wire.endTransmission();
    }
    delay(1000);
  }

  for (uint8_t i = 0; i < NOMBRE_DE_BACS; i++)
  {
    Wire.beginTransmission(ADRESSE_BASE_BACS + i);
    Wire.write(ETEINDRE_LEDS);
    Wire.endTransmission();
  }

  pinMode(BOUTON_VALIDER, INPUT);
}

bool etatPrecedentEtatBouton = RELACHE;

void loop()
{
  //lecture des entrées 
  byte reponseI2C;

  Wire.requestFrom(ADRESSE_BASE_BACS, NOMBRE_D_OCTETS);
  if(Wire.available())
  {
    reponseI2C = Wire.read();
    Serial.println(reponseI2C, BIN);
  }
  
  
  
  
  
  
  recevoirTrame();
  
  //piloter les leds en fonction de la trame
  // si le champ du décodage de la trame correspond au numéro du bac, alors allumer la led verte en fonction du numéro du champ. 
  bool etatActuel = etatBoutonValider();

    if (etatActuel == APPUYER && etatPrecedentEtatBouton == RELACHE)
    {
        String trame = envoyerTrame(fabriquerTrame(true));
        envoyerParBluetooth(trame);
        Serial.println("Trame envoyée : " + trame);
    }

    etatPrecedentEtatBouton = etatActuel;  //  fonctionne maintenant
    delay(50);
}

    






