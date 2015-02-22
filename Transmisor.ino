String titulo = "nRF24L01p V0.1 PTR ";
#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p transmisor(9,8);//CSN,CE MEGA
//nRF24L01p transmisor(10,9);//CSN,CE NANO
void setup(){
  titulo.concat(__DATE__);
  #define VERSION titulo  
  delay(150);
  Serial.begin(9600);
  Serial.println(VERSION);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  transmisor.channel(92);
  transmisor.TXaddress("Kerin");
  transmisor.RXaddress("Josue");
  transmisor.init();
  //Serial.println(transmisor.getStatus());
}

String message = "";

void loop(){
  if(Serial.available()>0){
    char character=Serial.read();
    if(character=='%'){
      transmisor.powerUp();
      message+=character;
      message+= '\0';
      if (message.length()> 32){
        Serial.println("Mensaje muy largo se enviara solo 32 caracteres");
      }
      transmisor.txPL(message);
      transmisor.send(FAST);
      Serial.print("Enviado: "); Serial.println(message);
      message="";
      transmisor._txIndex = 0;
      transmisor.flushTX();   
    }else{
      message+=character;
    }
  }
 if(transmisor.available()){
   String respuesta = "";
    transmisor.read();
    transmisor.rxPL(respuesta);
    Serial.println(respuesta);
    respuesta= "";
 }
}

