#include "transmettre.h"
#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial moduleBluetooth;
bool trameValide = false;

String entete = "$";
String finDeTrame = "%";
String valider = "V";
String acquittement = "A";

String buffer = "";

void intialiserBluetooth(String nomDuModule, uint16_t vitesse)
{
  moduleBluetooth.begin(nomDuModule);   // Nom du module visible en Bluetooth
}

bool bluetoothConnecte(void)
{
  return moduleBluetooth.hasClient();
}

void recevoirTrame() {
  while (moduleBluetooth.available()) {
    char c = moduleBluetooth.read();
    buffer += c;

    // On traite les trames complètes
    if (buffer.endsWith("\r\n")) {
      decodageTrame(buffer);
      buffer = "";
    }
  }
}

void decodageTrame(String data) {

  Serial.print(data);
  int start = 0;

  while (start < data.length()) {
    int end = data.indexOf("\r\n", start);
    if (end == -1) break;

    String trame = data.substring(start, end);
    start = end + 2; // passer "\r\n"

    // Vérification de la structure $X%
    if (trame.length() == 3 && trame.charAt(0) == '$' && trame.charAt(2) == '%') {
      char champ = trame.charAt(1);

      switch (champ) {
        case 'A':
          Serial.println("Trame A : Acquittement");
          break;
        case 'C':
          Serial.println("Trame C : Prise correcte");
          break;
        case 'E':
          Serial.println("Trame E : Erreur de prise");
          break;
        case 'V':
          Serial.println("Trame V : Étape validée");
          break;
        case 'D':
          Serial.println("Trame D : Début de processus");
          break;
        case 'F':
          Serial.println("Trame F : Fin de processus");
          break;
        default:
          Serial.print("Champ connu : ");
          Serial.println(champ);
      }
    } else {
      Serial.print("Trame invalide : ");
      Serial.println(trame);
    }
  }
}



String envoyerTrame(String trameAenvoyer)
{
  return entete + trameAenvoyer + finDeTrame;
}

String fabriquerTrame(bool boutonValider)
{
  if(boutonValider)
  {
    return String(valider);
  }
  return String(boutonValider); // Convertit booléen en "0" ou "1"
}

void envoyerParBluetooth(String message)
{
  moduleBluetooth.print(message);
  Serial.println(message);
}

