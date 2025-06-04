#ifndef TRANSMETTRE_H
#define TRANSMETTRE_H
#include <Arduino.h>
#include <String.h>

#define VITESSE_BLUETOOTH 9600
#define VITESSE_SERIE 9600
//#define AUCUN false
#define RECEPTION true



void initialiserBluetooth(String nomDuModule, uint16_t vitesse = 9600);
bool bluetoothConnecte(void);
String recevoirTrame();
char decodageTrame(String trame);
String fabriquerTrame(String champ);
void envoyerTrame(String trameAenvoyer);
bool trameValide(String trameRecue);

#endif  //TRANSMETTRE_H
