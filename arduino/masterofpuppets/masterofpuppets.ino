#include <SPI.h>
#include <Ethernet.h>
#include <IRremote.h>
#include <EthernetClient.h>
#include "ircommander.h"

#define DEBUG 1

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xBE };
byte ip[] = { 192 ,168 ,1 ,177 };
byte gateway[] = { 192 ,168 ,1 ,254 };
byte subnet[] = { 255 ,255 ,255 ,0 };
EthernetServer server(80);

String readString = String(30);


//byte server_send[] = {81, 174, 68, 58};
//EthernetClient client_send;
long lastConnectionTime = 0;
boolean lastConnected = false;
const int postingInterval = 10000;

IR_commander ircmd;


void setup(){
  //Initialize ethernet on master node
  Ethernet.begin(mac, ip, gateway, subnet);
  delay(1000);
  //pinMode(3, OUTPUT);
  //digitalWrite(3, LOW);
  Serial.begin(9600);
}

void loop(){

  /*if(!client_send.connected() && (millis() - lastConnectionTime > postingInterval)) {
    String tot;
    sendData(tot);
  }*/
  
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {//prende input
        if (client.available()) {
          char c = client.read();
          if (readString.length() < 30)
          {
            readString = readString + c;
          }
          if (c == '\n') {
            parseRequest(readString, client);
            readString="";
            client.stop();
          }
        }
      }
    delay(200);
  }
}

/* Implements the @controller@ */
void parseRequest(String readString,EthernetClient client){
          Serial.print(readString);
          Serial.print(client);
          Serial.print("----\n");
          client.println("HTTP/1.1 220 OK");
          
        
          if(readString.startsWith("GET /?out=11&status=1"))
          {
            client.print(ircmd.powerOnStereo());
          }
          if(readString.startsWith("GET /?out=11&status=0"))
          {
            Serial.print("\n 11 LOW \n");
            digitalWrite(3, LOW);
            client.print("{\"status\" : \"0\" , \"processed\" : \"ok\", \"out\" : \"");
            client.print(3);
            client.print("\"}");
          }
          if(readString.startsWith("GET /?out=all"))
          {
            //Serial.print(ircmd.getStatus());
            client.print(ircmd.getStatus());
          }
          
}

char * floatToString(char * outstr, double val, byte precision, byte widthp){
  char temp[16];
  byte i;
  double roundingFactor = 0.5;
  unsigned long mult = 1;
  for (i = 0; i < precision; i++)
  {
    roundingFactor /= 10.0;
    mult *= 10;
  }
  temp[0]='\0';
  outstr[0]='\0';
  if(val < 0.0){
    strcpy(outstr,"-\0");
    val = -val;
  }
  val += roundingFactor;
  strcat(outstr, itoa(int(val),temp,10));
  if( precision > 0) {
    strcat(outstr, ".\0"); // print the decimal point
  unsigned long frac;
  unsigned long mult = 1;
  byte padding = precision -1;
  while(precision--)
    mult *=10;
  if(val >= 0)
    frac = (val - int(val)) * mult;
  else
    frac = (int(val)- val ) * mult;
  unsigned long frac1 = frac;
  while(frac1 /= 10)
  padding--;
  while(padding--)
    strcat(outstr,"0\0");
  strcat(outstr,itoa(frac,temp,10));
  }
  if ((widthp != 0)&&(widthp >= strlen(outstr))){
    byte J=0;
    J = widthp - strlen(outstr);
    for (i=0; i< J; i++) {
      temp[i] = ' ';
    }
    temp[i++] = '\0';
    strcat(temp,outstr);
    strcpy(outstr,temp);
  }
  return outstr;
}

/*
void sendData(String thisData) {
  if (client_send.connect(server_send, 80)) {
    Serial.println("connecting...");
    client_send.print("GET /insert?ak=05b0b98c&read=");
    Serial.println("...sending ");
    Serial.println(thisData);
    Serial.println("\n");
    client_send.print(thisData);
    client_send.println(" HTTP/1.1");
    client_send.print("Host: www.domotichome.net\n");
    client_send.print("Content-Type: text/html\n");
    client_send.println("Connection: close\n");
    lastConnectionTime = millis();
    Serial.println("Done ");
    client_send.stop();
  }
  else {
    Serial.println("connection failed");
  }
} */
