#include <Arduino.h>
#include "affichage.h"
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Fonts/FreeSerifBold9pt7b.h"


Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);
oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADRESS); // démarrage du Oled en fixant son orientation et son adresse
oled.setTextSize(TAILLE_TEXTE);
oled.setFont(&FreeSerifBold9pt7b); // police de caractère *optionnelle
oled.setTextColor(SSD1306_WHITE);
oled.clearDisplay();

void initAfficheur(void)
{
    oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADRESS);
    oled.setTextSize(TAILLE_TEXTE);
    oled.setFont(&FREEBOLD);
    oled.setTextColor(SSD1306_WHITE);
    oled.clearDisplay();
}

void effacerAfficheur(void)
{
    oled.clearDisplay();
}

void afficher(int ligne, String texte, uint8_t alignement)
{
    switch (alignement)
    {
    case GAUCHE:
        alignement = GAUCHE;
        break;
    case CENTRE:
        alignement = OLED_WIDTH / 2 - texte.length() * 3.9;
        break;
    case DROITE:
        alignement = OLED_WIDTH - texte.length() * 3.9;
        break;

    default:
        break;
    }
    switch (ligne)
    {
    case LIGNE_1:
        oled.setCursor(alignement, OLED_HEIGHT * 1 / 4 - OFFSET_PIXEL);
        break;
    case LIGNE_2:
        oled.setCursor(alignement, OLED_HEIGHT * 1 / 2 - OFFSET_PIXEL);
        break;
    case LIGNE_3:
        oled.setCursor(alignement, OLED_HEIGHT * 3 / 4 - OFFSET_PIXEL);
        break;
    case LIGNE_4:
        oled.setCursor(alignement, OLED_HEIGHT - OFFSET_PIXEL);
        break;
    }
    oled.print(texte);
    oled.display();
}

bool actualiserAffichage(bool etatAcomparer)
{
    bool etat = false;
    return etat;
}

void afficherImage(const uint8_t *bitmap)
{
    oled.drawBitmap(ORIGINE_X, ORIGINE_Y, bitmap, OLED_WIDTH, OLED_HEIGHT, 1);
    oled.display();
}
void setup()
{
  initAfficheur();
  effacerAfficheur();
}

void loop(void)
{ 
  afficher(LIGNE_1, "Cybersecurite");
  afficher(LIGNE_2, "Informatique");
  afficher(LIGNE_3, "ELectronique");
  afficher(LIGNE_4, "& reseaux");
}