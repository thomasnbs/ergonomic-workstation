#ifndef BACS_H
#define BACS_H


#define NOMBRE_DE_BACS 8
#define ADRESSE_BASE_BACS 0x20

#define ALLUMER_LED_VERTE 0b11111101
#define ALLUMER_LED_ROUGE 0b11111110
#define ETEINDRE_LEDS 0b11111111
#define ROUGE 0
#define VERTE 0

#define CAPTEUR_DE_PRESENCE 0b11111011
#define NOMBRE_D_OCTETS 1
#define MASQUE_DE_PRESENCE_DE_MAIN 0x04 // 0b00000100

#define BOUTON_VALIDER 27
#define APPUYER true
#define RELACHE false



void commanderLedsbac(uint8_t numeroDuBac, byte etat);
void presenceMain(void);
void boutonValider(byte etatBouton);
//void bacSelectionne(uint8_t numroDuBac);



#endif //BACS