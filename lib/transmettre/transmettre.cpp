#include "transmettre.h"
#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial moduleBluetooth;
bool trameValide = false;
bool evenement = AUCUN; 
String entete = "$";
String finDeTrame = "%";
String acquittement = "A";
String valider = "V";

void intialiserBluetooth(String nomDuModule, uint16_t vitesse)
{
  moduleBluetooth.begin(nomDuModule);
  moduleBluetooth.begin(vitesse);
}

bool bluetoothConnecte(void)
{

   return moduleBluetooth.hasClient();
}

String recevoirTrame()
{
 String trameRecue = "";
 //while(!trameRecue.startsWith(ENTETE) && !trameRecue.endsWith(FIN_DE_TRAME)){
   if(moduleBluetooth.available()>0){
     trameRecue = moduleBluetooth.readString();
     }
return trameRecue;
}

String fabriquerTrame(bool BoutonValider)
{
  String trame = (String)BoutonValider;
  return trame;
}

String envoyerTrame(String trameAenvoyer)
{
  String trameEnvoyer = "";
  trameEnvoyer = entete + trameAenvoyer + finDeTrame;
  return trameEnvoyer;
}

String lireTrame()
{
  if (moduleBluetooth.available()) // récupere les donnees du BT 
  {
    Serial.write(moduleBluetooth.read()); 
  } 
  return lireTrame();
}


String recevoirTrame(String trameRecue)
{
  trameRecue = "";
  if(trameRecue.startsWith(entete)&&trameRecue.endsWith(finDeTrame))
  {
    trameValide = true;
  }
}