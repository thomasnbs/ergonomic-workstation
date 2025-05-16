#ifndef TRANSMETTRE_H
#define TRANSMETTRE_H
#include <Arduino.h>
#include <String.h>

#define VITESSE_BLUETOOTH 9600
#define VITESSE_SERIE 9600
#define AUCUN false
#define RECEPTION true

#define ENTETE  $$
#define FIN_DE_TRAME %%
#define ACQUITTEMENT A
#define TRAME_RECUE ""


void intialiserBluetooth(String nomDuModule, uint16_t vitesse = VITESSE_BLUETOOTH);
bool bluetoothConnecte(void);

#endif  //TRANSMETTRE_H