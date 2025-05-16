#include "transmettre.h"
#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial moduleBluetooth;

void intialiserBluetooth(String nomDuModule, uint16_t vitesse)
{
  moduleBluetooth.begin(nomDuModule);
  moduleBluetooth.begin(vitesse);
}

bool bluetoothConnecte(void){

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




void envoyerTrame(String trameAenvoyer)
{
    
   moduleBluetooth.print(trameAenvoyer);
   
}

