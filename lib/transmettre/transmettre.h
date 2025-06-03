#ifndef TRANSMETTRE_H
#define TRANSMETTRE_H
#include <Arduino.h>
#include <String.h>

#define VITESSE_BLUETOOTH 9600
#define VITESSE_SERIE 9600
#define AUCUN false
#define RECEPTION true


void intialiserBluetooth(String nomDuModule, uint16_t vitesse = 9600);
bool bluetoothConnecte(void);
void recevoirTrame();
void decodageTrame(String trame);
String fabriquerTrame(String);
void envoyerTrame(String trameAenvoyer);


#endif  //TRANSMETTRE_H
