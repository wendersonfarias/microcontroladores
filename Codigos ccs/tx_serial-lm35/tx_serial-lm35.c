//#include "C:\Users\wende\Desktop\MICRO\microcontroladores\Codigos ccs\tx_serial-lm35\tx_serial-lm35.h"

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
   float leitura;
   
   
   
 
   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_16);
   
 
   set_adc_channel(0);
   delay_us(20);

   while(TRUE){
      leitura = read_adc();
      
      
      
      
      
      
      
    
     fprintf(leitura_lm35,"%f",leitura);
     delay_ms(200);
      
   }

}

//105 i
//102 f
//109 m
//116 t
//
