/**
 * 
 * 
 * 
 * 
 * 
 * init le bus I2c
 * initialiser les IO et leds
 * allumer les leds : en vert puis vert pour initialisation
 * initiliatilser le bluetooth
 * allumer les leds : en rouge après initialisation
 * 
 * 
 * 
 * 
 * interroger les bacs : lire le bus I2c
 *  lire état de chaque capteur de présence par bac
 *  stocker la valeur de l'état dans un tableau/octet
 * comparer le bac sélectionner et le bac détecté
 *  si  différence alors faire sonner le buzzer
 *   sinon rien
 * 
 * 
 */


#include <Arduino.h>
#include <Wire.h>
#include <String.h>
#include "BluetoothSerial.h"

#define VITESSE_BLUETOOTH 9600
#define VITESSE_SERIE 9600


#define NOMBRE_DE_BACS  8

#define ADRESSE_BASE_BACS   0x20

#define NUMERODUBAC_1 0
#define NUMERODUBAC_2 1
#define NUMERODUBAC_3 2
//#define numeroDuBac_8 7 // adresse du dernièr bac

#define ALLUMER_LED_VERTE  0b11111101
#define ALLUMER_LED_ROUGE  0b11111110
#define ETEINDRE_LEDS      0b11111111
#define ROUGE 0
#define VERTE 0

#define NOMBRE_D_OCTETS 1
#define MASQUE_DE_PRESENCE_DE_MAIN 0x04 // 0b00000100

#define AUCUN false
#define RECEPTION true

String entete ="$$";
String finDeTrame = "%%";
String acquittement = "A";
String trameRecue = "";
bool trameValide = false;
uint8_t bacSelectionne = 0;
bool evenement = AUCUN;

BluetoothSerial ergonomicWorkstation;   // instanciation de l'objet "ergonomicWorkstation" dans la classe BluetoothSerial

bool presenceMain = false;
//bool presenceBacs [3] = {ADRESSEBASEDUBAC_1, ADRESSEBASEDUBAC_2, ADRESSEBASEDUBAC_3};

void commanderLedsBac(uint8_t numeroDuBac, byte etat){
  numeroDuBac--;
  Wire.beginTransmission(ADRESSE_BASE_BACS+numeroDuBac); // Début de la transmission à l'adresse 0x20
  Wire.write(etat);        
  Wire.endTransmission();
}

void setup()
{
  Serial.begin(VITESSE_SERIE);
  Wire.begin();         //init le bus I2c
  for(uint8_t i=0;i<NOMBRE_DE_BACS;i++){
    Wire.beginTransmission(ADRESSE_BASE_BACS+i); // Début de la transmission à l'adresse 0x20
    Wire.write(ALLUMER_LED_VERTE);        
    Wire.endTransmission();
  }
   // allumer les leds : en vert puis vert pour initialisation

  ergonomicWorkstation.begin("EWS_4.0");    //initiliatilser le bluetooth
delay(1000);

for(uint8_t i=0;i<NOMBRE_DE_BACS;i++){
  Wire.beginTransmission(ADRESSE_BASE_BACS+i); // Début de la transmission à l'adresse 0x20
  Wire.write(ALLUMER_LED_ROUGE);        
  Wire.endTransmission();
}

delay(1000);
for(uint8_t i=0;i<NOMBRE_DE_BACS;i++){
  Wire.beginTransmission(ADRESSE_BASE_BACS+i); // Début de la transmission à l'adresse 0x20
  Wire.write(ETEINDRE_LEDS);        
  Wire.endTransmission();
}

}
void loop() 
{

  if(ergonomicWorkstation.available()>0){
       
    trameRecue = ergonomicWorkstation.readString();
    if(trameRecue.startsWith(entete)){  //&&trameRecue.endsWith(finDeTrame)
      trameValide=true;
    }
    if(trameValide){
      String trameAenvoyer = entete + acquittement + finDeTrame;
      ergonomicWorkstation.print(trameAenvoyer);
      trameValide=false;
      //Serial.println(trameRecue.length());
      //Serial.println(finDeTrame.length());
      trameRecue = trameRecue.substring(entete.length(),trameRecue.length()-finDeTrame.length());
      bacSelectionne = trameRecue.toInt();
      
      evenement = RECEPTION;

      Serial.println(bacSelectionne);
    
  }
    ergonomicWorkstation.flush();
  }

  if(evenement == RECEPTION){
    commanderLedsBac(bacSelectionne,ALLUMER_LED_VERTE);
    delay(1000);
    commanderLedsBac(bacSelectionne,ETEINDRE_LEDS);
    evenement = AUCUN;


  }
  
  //Wire.beginTransmission(ADRESSE_BASE_BACS+bacSelectionne-1); // Début de la transmission à l'adresse 0x20
  //Wire.write(ALLUMER_LED_VERTE);        
  //Wire.endTransmission();
  


// 

/*
  Wire.requestFrom(ADRESSEBASEDUBAC_1 + NUMERODUBAC_1, NOMBRE_D_OCTETS); // Demande de 1 octet à l'adresse 0x20
  Wire.beginTransmission(ADRESSEBASEDUBAC_1 + NUMERODUBAC_1); // Début de la transmission à l'adresse 0x20
  if(Wire.available()>0) 
  {
    uint8_t octetDuBac = Wire.read();
    bool presenceMain = (octetDuBac & MASQUE_DE_PRESENCE_DE_MAIN) ; // Vérifie si le bit de présence de la main est à 0
    //stockage dans tableau ou création d'un octet de présence
    presenceMain[presenceBacs] = (octetDuBac & MASQUE_DE_PRESENCE_DE_MAIN);
    Wire.endTransmission(); 

  } 
*/ 
  //for (int i = 0; i < 3 ; i ++)
  //ergonomicWorkstation.println(presenceBacs);
}
