#ifndef TRANSMETTRE_H
#define TRANSMETTRE_H
#include <Arduino.h>
#include <String.h>

#define VITESSE_BLUETOOTH 9600
#define VITESSE_SERIE 9600
#define AUCUN false
#define RECEPTION true




void intialiserBluetooth(String nomDuModule, uint16_t vitesse = VITESSE_BLUETOOTH);
bool bluetoothConnecte(void);
//fabriquer une trame
String fabriquerTrame(bool BoutonValider);
// trame à envoyer
String envoyerTrame(String trameAenvoyer);
//lire la trame
String lireTrame();
// trame à recevoir
String recevoirTrame();


#endif  //TRANSMETTRE_H
