#include "transmettre.h"
#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial moduleBluetooth;


String entete = "$";
String finDeTrame = "%";
String valider = "V";
String acquittement = "A";
String priseCorrecte = "C";

String buffer = "";


void initialiserBluetooth(String nomDuModule, uint16_t vitesse)
{
  moduleBluetooth.begin(nomDuModule);   // Nom du module visible en Bluetooth
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
  }

  return trameRecue;
}

char decodageTrame(String trame) 
{
 //data = $X%
 Serial.println("==> Entrée dans decodageTrame");
  int start = 0;

  while (start < trame.length()) 
  {

    // Vérification de la structure $X%
      trame = trame.substring(entete.length(), trame.length() - finDeTrame.length());
      Serial.print("Trame decode : ");
      Serial.println(trame);
      char champ = trame.charAt(0);
      Serial.print("Champ : ");
      Serial.println(champ);
      if (champ >= '1' && champ <= '6') {
        return champ; // Retourne le champ du bac sélectionné
      }
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
    
  }
  return '\0'; // Retourne une chaîne vide si aucune trame valide n'est trouvée
}

void envoyerTrame(String trameAenvoyer)
{
  moduleBluetooth.println(trameAenvoyer);
}

String fabriquerTrame(String champ)
{
  
  String trameFabriquee = entete + champ + finDeTrame;
  return trameFabriquee;
}

bool trameValide(String trameRecue)
{
  trameRecue.trim(); // Nettoie les \r ou espaces

  if (trameRecue.length() == 3 && trameRecue.charAt(0) == '$' && trameRecue.charAt(2) == '%') 
  {
    return true;
  } 
  else 
  {
    Serial.print("Trame invalide : ");
    Serial.println(trameRecue);
    return false;
  }
}



