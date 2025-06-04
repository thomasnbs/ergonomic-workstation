#include <Arduino.h>
#include <Wire.h>
#include "transmettre.h"
#include "bacs.h"
// #include "affichage.h"

#define NOM_DE_LA_STATION "EWS_4.0"
#define BLUETOOTH_ACTIF
#define CARACTERE_NULL '\0'

void setup()
{

  Serial.begin(VITESSE_SERIE);
  Wire.begin();
  pinMode(BOUTON_VALIDER, INPUT);

#ifdef BLUETOOTH_ACTIF

  initialiserBluetooth(NOM_DE_LA_STATION);

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
  byte reponseI2C;
  String trameRecue = recevoirTrame(); // Recevoir la trame Bluetooth
  char champRecu = CARACTERE_NULL;

  // vérifier si la trame reçue est valide et envoyer acquittement
  if (trameValide(trameRecue))
  {

    Serial.print("Trame reçue : ");
    Serial.println(trameRecue); // Afficher la trame reçue

    envoyerTrame(fabriquerTrame("A"));     // Envoie une trame d'acquittement
    champRecu = decodageTrame(trameRecue); // si la trame est valide, extraire le champ de la trame

    Serial.print("Champ reçu : ");
    Serial.println(champRecu); // Afficher le champ reçu
  }
  else
  {
    // sinon ne rien faire
  }
  // traiter les champs

  uint8_t bacSelectionne = (int)champRecu; // Convertit le champ reçu en entier pour identifier le bac sélectionné
  // allumer la LED verte du bac sélectionné

  for (int i = 0; i < NOMBRE_DE_BACS; i++)
  {
    Wire.requestFrom(ADRESSE_BASE_BACS + i, OCTET_DU_BAC);
    if (Wire.available() > 0)
    {
      reponseI2C = Wire.read();

      if (!(reponseI2C & MASQUE_DE_PRESENCE_DE_MAIN))
      {
        uint8_t bacIdentifie = i + 1; // Le bac est identifié par son numéro (1 à 6)
        Serial.print("Bac ");
        Serial.print(bacIdentifie);
        // détecter la présence de la main dans le bac sélectionné
        // comparer le bac sélectionné avec le bac identifié
        // si le bac identifié est correct, envoyer une trame de prise correcte, clignoter la LED verte du bac sélectionné
        // sinon, envoyer une trame d'erreur de prise, allumer la LED rouge du bac sélectionné, faire sonner le buzzer du bac sélectionné

        // bacSelectionne(trameRecue.toInt() - 1); // Convertit la trame reçue en entier et sélectionne le bac correspondant
        envoyerTrame(fabriquerTrame("C"));
        commanderLedsBac(i, ALLUMER_LED_VERTE); // Allume la LED verte du bac sélectionné
      }
    }
  }
}
