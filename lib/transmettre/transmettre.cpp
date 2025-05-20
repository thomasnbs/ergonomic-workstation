#include "transmettre.h"
#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial moduleBluetooth;
bool trameValide = false;

String entete = "$";
String finDeTrame = "%";
String valider = "V";
String acquittement = "A";

void intialiserBluetooth(String nomDuModule, uint16_t vitesse)
{
  moduleBluetooth.begin(nomDuModule);   // Nom du module visible en Bluetooth
  Serial.println("Bluetooth initialisé");
}

bool bluetoothConnecte(void)
{
  return moduleBluetooth.hasClient();
}

String recevoirTrame()
{
  String trameRecue = "";

  if (moduleBluetooth.available() > 0)
  {
    trameRecue = moduleBluetooth.readStringUntil('\n');
    trameRecue.trim();

    if (trameRecue.startsWith(entete) && trameRecue.endsWith(finDeTrame))
    {
      trameValide = true;
      trameRecue = trameRecue.substring(entete.length(), trameRecue.length() - finDeTrame.length());
    }
  }

  return trameRecue;
}


String envoyerTrame(String trameAenvoyer)
{
  return entete + trameAenvoyer + finDeTrame;
}

String fabriquerTrame(bool boutonValider)
{
  return String(boutonValider); // Convertit booléen en "0" ou "1"
}

void envoyerParBluetooth(String message)
{
  moduleBluetooth.print(message);
}

