#include <Arduino.h>
#include <Wire.h>
#include "transmettre.h"
#include "bacs.h"

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


void loop()
{
  String trame = recevoirTrame();

  if (trame != "")
  {
    Serial.println("Trame reçue : " + trame);

    // Envoi d'un acquittement "A" ou "V"
    String ack = envoyerTrame("A");  // Ou "V", selon ton protocole
    envoyerParBluetooth(ack);

    Serial.println("Acquittement envoyé : " + ack);
  }

  delay(100); // Petite pause pour éviter les lectures trop rapides
}


