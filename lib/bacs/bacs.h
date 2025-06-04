#ifndef BACS_H
#define BACS_H

#define NOMBRE_DE_BACS 6
#define ADRESSE_BASE_BACS 0x20 // correspond au bac n°1
#define NUMERO_DU_BAC_1 0x21
#define NUMERO_DU_BAC_2 0x22
#define NUMERO_DU_BAC_3 0x23
#define NUMERO_DU_BAC_4 0x24

#define ALLUMER_LED_VERTE 0b11111101
#define ALLUMER_LED_ROUGE 0b11111110
#define ETEINDRE_LEDS 0b11111111
#define BUZZER 0b11101111
#define BUZZER_ET_LED_ROUGE 0b11101110

#define ROUGE 0
#define VERTE 0

#define CAPTEUR_DE_PRESENCE 0b11111011
#define OCTET_DU_BAC 1
#define MASQUE_DE_PRESENCE_DE_MAIN 0x04

#define BOUTON_VALIDER 27
#define APPUYER HIGH
#define RELACHE LOW

void commanderLedsBac(uint8_t numeroDuBac, byte etat);
bool etatBoutonValider(); // déclaration correcte
bool etatPrecedentBouton();
void bacSelectionne(uint8_t numeroDuBac);
void signalerUnEcart(uint8_t numeroDuBac, byte etat);
// void presenceMain(uint8_t octetDuBac);

#endif // BACS_H
