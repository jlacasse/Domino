#include "device.h"
#include "ircommander.h"
#include "IRremote.h"
/** 

Classe per pilotare un IR connesso al tre
si basa sulla libreria di shirrif, programmata per gestire
tre dispositivi privati

*/
IRsend irsend;

String IR_commander::powerOnStereo(){
  #ifdef DEBUG
  Serial.print("\n 11 STEREO POWER ON \n");
  #endif
  
  //digitalWrite(3, HIGH);
  String ret = "";
  
  togglePower();
  ret = ("{\"status\" : \"1\" , \"processed\" : \"ok\" , \"out\" : \"");
  ret +=(3);
  ret +=("\"}");
  return ret;
}

String IR_commander::getStatus(){
    #ifdef DEBUG
    Serial.print("\n OUT ALL\n");
    #endif
    String tto = "";
          tto = ("{\"ip\" : \"192.168.1.177\", ");
          tto += ("\"devices\" : ");
          tto += ("[{ \"type\" : \"irrigation\", \"name\" : \"IR commander\", \"out\" : \"");
          tto += ("11");
          tto += ("\"}");
          tto += ("]}");
         return tto;
}

void IR_commander::testtuner(){
  tuner();
  delay(2000);
  increaseVolume();
  lowerVolume();
}

/* mette su il CD e play terza traccia*/
void IR_commander::testCd(){
  cd();
  next();
  next();
  next();
  
  prev();
  cdplay();
  delay(10000);
  cdstop();
}

void IR_commander::lowerVolume(){
  irsend.sendPanasonic(0x40040500, 0x8481); // attiva volume
  delay(200);
  irsend.sendPanasonic(0x40040500, 0x8481); // volume giu
  delay(3500);//Attendi che sparisca
}

void IR_commander::increaseVolume(){
  irsend.sendPanasonic(0x40040500, 0x401); // attiva volume
  delay(200);
  irsend.sendPanasonic(0x40040500, 0x401); // volume su
  delay(3500);//Attendi che sparisca
}
/* accende spegne */
void IR_commander::togglePower(){
   for (int i = 0; i < 3; i++) {
      irsend.sendPanasonic(0x40040538, 0xBC81); // i rincoglioniti tengono premuto un secondo
      delay(250);//mando cinque volte come i rincoglioniti entro un secondo
    }
}
void IR_commander::cdplay(){
      irsend.sendPanasonic(0x40040538, 0x506D); 
      delay(300);
}
void IR_commander::cdstop(){
      for (int i = 0; i < 5; i++) {
      irsend.sendPanasonic(0x40040538, 0x3D); // stop è idempotente
      delay(250);//manda che ti passa
    }
}
void IR_commander::next(){
      irsend.sendPanasonic(0x40040538, 0x526F); // i rincoglioniti tengono premuto un secondo
      delay(30);
}void IR_commander::prev(){
      irsend.sendPanasonic(0x40040538, 0x92AF); // i rincoglioniti tengono premuto un secondo
      delay(300);
}

void IR_commander::cd(){
  irsend.sendPanasonic(0x40040500, 0x292C); // metti CD
  delay(800);//tempo caricamento disco
}
void IR_commander::tuner(){
  irsend.sendPanasonic(0x40040520, 0x2500); // radio
  delay(300);
}
void IR_commander::aux(){
  irsend.sendPanasonic(0x40040500, 0x595C); // volume su
}

