//#include "C:\Users\wende\Desktop\MICRO\microcontroladores\Codigos ccs\serial_lm35\serial_lm35.h"
#include <16F877A.h>

#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=20000000)
#use rs232(baud=1200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=leitura_lm35)



void main()
{
   int16 leitura;
   
   int8 possiveisValores[11];
   int maior ;
   int cont;
   int temperaturaBruta=0;
   


   
   setup_adc(ADC_CLOCK_DIV_16);
   setup_adc_ports(AN0);
 
   set_adc_channel(0);
   delay_us(20);

   
   while(TRUE){
      maior = 0;
      for(cont = 0; cont <= 10; cont++){
         leitura = read_adc();
         delay_us(10);
         if(leitura<= 255){
             possiveisValores[cont] = (int8)leitura;
         }
         else{
             possiveisValores[cont] = 255;
         }
      
      }
      
       for(cont = 0; cont <= 10; cont++){
         if(maior < possiveisValores[cont]) {
            maior = possiveisValores[cont];
         }
      
      }
      
      temperaturaBruta = maior;
      
      delay_ms(20);
      
      fprintf(leitura_lm35, "%u", temperaturaBruta);
      
      
      
   
   }

}




