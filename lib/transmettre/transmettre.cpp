#include "transmettre.h"
#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial moduleBluetooth;
bool trameValide = false;
bool evenement = AUCUN; 
String entete = "$";
String finDeTrame = "%";

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

String fabriquerTrame(String typeDeTrame)
{
  String trameFabriquee = "";
  trameFabriquee = entete + typeDeTrame + finDeTrame;
  return trameFabriquee;
}

String envoyerTrame(String trameAenvoyer)
{
  String trameEnvoyer = "";
  trameEnvoyer = entete + trameAenvoyer + finDeTrame;
  return trameEnvoyer;
  moduleBluetooth.print(trameEnvoyer);
  Serial.print(trameEnvoyer);
}

String lireTrame(String lectureDeTrame)
{
  Serial.print(lectureDeTrame);
  return lectureDeTrame;
}


String recevoirTrame(String trameRecue)
{
  trameRecue = "";
  if(trameRecue.startsWith(entete)&&trameRecue.endsWith(finDeTrame))
  {
    trameValide = true;
  }
}
