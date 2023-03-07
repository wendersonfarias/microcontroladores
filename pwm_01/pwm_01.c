//#include "C:\Users\wende\Desktop\MICRO\pwm_01\pwm_01.h"

#include <16F877A.h>
#device adc=8

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



int16 ton=0, toff;
unsigned int16 cont;
int1 ordem = 0; //0 - crescente - 1 decrescente

void main()
{

   while(TRUE){
      // 1000 us -> 
      
      
      for(ton= 0; ton < 1000 ; ton+=10  ){
            output_high(PIN_C2);
            delay_us(ton);
            
            toff = 1000 - ton;
            
            output_low(PIN_C2);
            delay_us(toff);
      }
      
         
  }
   
} 
   
   
      
   
   
   



