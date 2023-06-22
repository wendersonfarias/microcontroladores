#include <Wire.h>
#include "Adafruit_SHT31.h"
Adafruit_SHT31 sht31 = Adafruit_SHT31();

float somatorioPID = 0.0, 
ultimaTemperatura = 0.0, 
proporcional = 0.0, 
integrativo = 0.0, 
derivativo = 0.0, 

erro = 0.0;


float temperaturaReferencia = 35.0;

long contador = 0;
int contadorPID = 0;


void setup() {
      pinMode(13,OUTPUT);
      digitalWrite(13,LOW);
    
      
      Serial.begin(9600);
      delay(10);
      //Serial.println("SHT31 test");
      if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
        //Serial.println("Couldn't find SHT31");
      while (1) delay(1);
      }

}

void loop() {

  //if(contador > 500000 * 2){
       float temperaturaSHT = sht31.readTemperature();
    
       if (! isnan(temperaturaSHT)) {  // check if 'is not a number'
          erro = temperaturaReferencia - temperaturaSHT;
         proporcional = erro * 100;                                  // kp
         integrativo += erro * 0.01;                                 // ki
         derivativo = (ultimaTemperatura - temperaturaSHT) * 0.01;  // kd
      
         ultimaTemperatura = temperaturaSHT;
      
         somatorioPID = proporcional + integrativo + derivativo;

        /* String dados = String((int)temperaturaReferencia) + "," +
               String((int)temperaturaSHT) + "," +
               String((int)erro);
        */
        //Serial.println(dados);

        Serial.print((int)temperaturaReferencia);
        Serial.print(',');
        Serial.print((int)temperaturaSHT);
        Serial.print(',');
        Serial.println((int)erro);
       

    delay(500);

    if(temperaturaSHT >= temperaturaReferencia){
      digitalWrite(13,LOW);
      Serial.print("desligado");
    }else{
      digitalWrite(13,HIGH);
      Serial.print("ligado");
    }
       
   }

   
    /*
   if(contadorPID <= somatorioPID){
        digitalWrite(14,HIGH);
    }else{
        digitalWrite(14,LOW);
    }

   contadorPID++;
   delayMicroseconds(50);

   if(contador > 500000){
      contador == 0;
   }
   
   if(contadorPID >= 20) {
      contadorPID = 0;
      contador += 50;
   }
    */
   
   
}
