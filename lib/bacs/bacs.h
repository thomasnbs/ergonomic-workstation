#ifndef BACS_H
#define BACS_H

#define NOMBRE_DE_BACS 8
#define ADRESSE_BASE_BACS 0x20
#define NUMERO_DU_BAC_1 0x21
#define NUMERO_DU_BAC_2 0x22
#define NUMERO_DU_BAC_3 0x23
#define NUMERO_DU_BAC_4 0x24

#define ALLUMER_LED_VERTE 0b11111101
#define ALLUMER_LED_ROUGE 0b11111110
#define ETEINDRE_LEDS 0b11111111
#define ROUGE 0
#define VERTE 0

#define CAPTEUR_DE_PRESENCE 0b11111011
#define NOMBRE_D_OCTETS 1
#define MASQUE_DE_PRESENCE_DE_MAIN 0x04

#define BOUTON_VALIDER 27
#define APPUYER HIGH
#define RELACHE LOW


void commanderLedsBac(uint8_t numeroDuBac, byte etat);
bool etatBoutonValider();  // déclaration correcte
bool etatPrecedentBouton();
void decodageBacs();
//void presenceMain(uint8_t octetDuBac, byte capteurValeur);
//void buzzer();



#endif // BACS_H
