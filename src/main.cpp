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
 #include "transmettre.h"
 #include "bacs.h"

 //#define numeroDuBac_8 7 // adresse du dernièr bac

 #define NOM_DE_LA_STATION "EWS_4.0"

#define CAPTEUR_DE_PRESENCE 0b11111011
#define NOMBRE_D_OCTETS 1
#define MASQUE_DE_PRESENCE_DE_MAIN 0x04 // 0b00000100



void setup()
{
  Serial.begin(VITESSE_SERIE);
  Wire.begin();         //init le bus I2c
  
intialiserBluetooth(NOM_DE_LA_STATION);
while(!bluetoothConnecte()){

  for(uint8_t i=0;i<NOMBRE_DE_BACS;i++){
    Wire.beginTransmission(ADRESSE_BASE_BACS+i); // Début de la transmission à l'adresse 0x20
    Wire.write(ALLUMER_LED_VERTE);        
    Wire.endTransmission();
  }
 
delay(1000);

for(uint8_t i=0;i<NOMBRE_DE_BACS;i++){
  Wire.beginTransmission(ADRESSE_BASE_BACS+i); // Début de la transmission à l'adresse 0x20
  Wire.write(ALLUMER_LED_ROUGE);        
  Wire.endTransmission();
  }
delay(1000);
}

for(uint8_t i=0;i<NOMBRE_DE_BACS;i++){
  Wire.beginTransmission(ADRESSE_BASE_BACS+i); // Début de la transmission à l'adresse 0x20
  Wire.write(ETEINDRE_LEDS);        
  Wire.endTransmission();
 } 
}

///////////////////////////////////////////////////////////////////////
void loop() 
{

  /*if(BLUETOOTH_SERIAL.available()>0){
       
    trameRecue = BLUETOOTH_SERIAL.readString();
    if(trameRecue.startsWith(entete)){  //&&trameRecue.endsWith(finDeTrame)
      trameValide=true;
    }
    if(trameValide){
      String trameAenvoyer = entete + acquittement + finDeTrame;
      BLUETOOTH_SERIAL.print(trameAenvoyer);
      trameValide=false;
      //Serial.println(trameRecue.length());
      //Serial.println(finDeTrame.length());
      trameRecue = trameRecue.substring(entete.length(),trameRecue.length()-finDeTrame.length());
      bacSelectionne = trameRecue.toInt();
      
      evenement = RECEPTION;

      Serial.println(bacSelectionne);
    
  }
    BLUETOOTH_SERIAL.flush();
  }*/
}
  /*Wire.beginTransmission(ADRESSE_BASE_BACS+bacSelectionne-1); // Début de la transmission à l'adresse 0x20
  Wire.write(ALLUMER_LED_VERTE);        
  Wire.endTransmission();
  





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
 
  //for (int i = 0; i < 3 ; i ++)
  //ergonomicWorkstation.println(presenceBacs);
  */