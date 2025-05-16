#ifndef BACS_H
#define BACS_H

#define NOMBRE_DE_BACS 8
#define ADRESSE_BASE_BACS 0x20
#define ALLUMER_LED_VERTE 0b11111101
#define ALLUMER_LED_ROUGE 0b11111110
#define ETEINDRE_LEDS 0b11111111
#define ROUGE 0
#define VERTE 0
#define AUCUN false
#define RECEPTION true 

void commanderLedsbac(uint8_t numeroDuBac, byte etat);
void presenceMain(void);

#endif //BACS