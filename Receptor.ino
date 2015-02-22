#include <SPI.h>
#include <nRF24L01p.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(A5,A4,3,4,5,6);
#define BL A3


//Variables de RF
String message;

nRF24L01p receptor(A2,A1);//CSN,CE 
unsigned long tiempo;
void setup() 
{
  Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receptor.channel(92);
  receptor.RXaddress("Kerin");
  receptor.TXaddress("Josue");
  receptor.init();
  // Setup motors
  lcd.begin(16,2);
  lcd.clear();
  delay(5);
  Serial.print("Listo");
  lcd.setCursor(0,0);
  lcd.print("Recibido :");
  tiempo=millis();
}

void loop() 
{
  // Recepcion de mensaje ------------------------------
  if(receptor.available()){
    receptor.read();
    lcd.clear();
    delay(5);
    lcd.setCursor(0,0);
    lcd.print("Recibido :");
    receptor.rxPL(message);
    lcd.setCursor(0,1);
    lcd.print(message);
    lcd.noCursor();
    lcd.noBlink();
    Serial.println(message);
    tiempo=millis();
  }
  if(millis()-tiempo>1000){
    lcd.setCursor(0,1);
    lcd.print(" No Recibiendo  ");
  }
  message= "";    

}


