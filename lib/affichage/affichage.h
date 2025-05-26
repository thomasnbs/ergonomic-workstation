/* Programme de gestion de l'afficheur
 * Oled 0.96" I2C 128x64
 */
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Liaison I2C et afficheur Oled

#define SDA_PIN 21
#define SCL_PIN 22
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADRESS 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OFFSET_PIXEL 1
#define GAUCHE 0
#define CENTRE 1
#define DROITE 2

#define FONTS ArialMT_Plain_16      // Police de caractères par défaut
#define FREEBOLD FreeSerifBold9pt7b // Police de caractères par défaut
#define TAILLE_TEXTE 1
#define LIGNE_1 0
#define LIGNE_2 1
#define LIGNE_3 2
#define LIGNE_4 3
#define ORIGINE_X 0
#define ORIGINE_Y 0

void initAfficheur(void);
void effacerAfficheur(void);
void afficher(int ligne, String texte, uint8_t alignement = GAUCHE);
bool actualiserAffichage(bool etatAcomparer);
void afficherImage(const uint8_t *bitmap);

#endif // AFFICHAGE_H