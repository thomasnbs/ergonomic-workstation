#include <Arduino.h>
#include <Wire.h>
#include "transmettre.h"
#include "bacs.h"
//#include "affichage.h"

#define NOM_DE_LA_STATION "EWS_4.0"
#define BLUETOOTH_ACTIF

void setup()
{
  Serial.begin(VITESSE_SERIE);
  Wire.begin();
  pinMode(BOUTON_VALIDER, INPUT);

  #ifdef BLUETOOTH_ACTIF

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

#endif


  for (uint8_t i = 0; i < NOMBRE_DE_BACS; i++)
  {
  commanderLedsBac(i, ALLUMER_LED_VERTE);
  }
delay(1000);
  for (uint8_t i = 0; i < NOMBRE_DE_BACS; i++)
  {
    Wire.beginTransmission(ADRESSE_BASE_BACS + i);
    Wire.write(ETEINDRE_LEDS);
    Wire.endTransmission();
  }


  
}
//////////////////////////////////////////////////////////////////////
bool etatPrecedentEtatBouton = RELACHE;

void loop()
{
  //lecture des entrées 
  byte reponseI2C;
    for (int i = 0; i <NOMBRE_DE_BACS; i++)
  {
    Wire.requestFrom(ADRESSE_BASE_BACS + i, OCTET_DU_BAC);
    if(Wire.available() >0)
    {
      reponseI2C = Wire.read();

      if (!(reponseI2C & MASQUE_DE_PRESENCE_DE_MAIN))
      {
        uint8_t bacIdentifie = i + 1; // Le bac est identifié par son numéro (1 à 6)
        Serial.print("Bac ");
        
        Serial.print(bacIdentifie);
        envoyerTrame(fabriquerTrame(String(bacIdentifie)));
        commanderLedsBac(i, ALLUMER_LED_VERTE);
        delay(1000);
        commanderLedsBac(i, ETEINDRE_LEDS);
      }
        
      
    }
  }

  recevoirTrame();
  
  //piloter les leds en fonction de la trame
  // si le champ du décodage de la trame correspond au numéro du bac, alors allumer la led verte en fonction du numéro du champ. 
 /* bool etatActuel = etatBoutonValider();

    if ((etatActuel == APPUYER) && (etatPrecedentEtatBouton == RELACHE))
    {
      //  String trame = envoyerTrame(fabriquerTrame(true));
      //  envoyerParBluetooth(trame);
      //  Serial.println("Trame envoyée : " + trame);
    }

    etatPrecedentEtatBouton = etatActuel;  //  fonctionne maintenant
    delay(50);*/
}



    






