//#include "C:\Users\wende\Desktop\MICRO\microcontroladores\Codigos ccs\trabalho_radio_serial\tx\tx.h"
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
#use I2C(MASTER, SDA = PIN_B6, SCL = PIN_B7, fast = 100000)
#use rs232(baud=1200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=serial1)

#include "C:\Users\wende\Desktop\MICRO\microcontroladores\Codigos ccs\trabalho_radio_serial\drives\SHT3x.c"
void main()
{

   float TS = 0.0;    
   float HS = 0.0;   
   int8 t;
   int8 h;

   
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   
   set_adc_channel(0);
   delay_us(100);
   
   SHT3x_init(); 

   delay_ms(100);

   while(TRUE){
   
       SHT3x_read_temp_humidity(&HS, &TS);
      
       
       t = (int8)TS; //conversao float para int8; ex. 30.28 -> 30;
       
       h = (int8)HS; //conversao float para int8; ex. 80.32 -> 80;

        //envia os dados via serial do pic, 
        //envia a temperatura e logo depois umidade;
        // e uma quebra de linha para sinalizar fim de transmissao
        
       fprintf(serial1,"%u %u P", t,h);
   
   
  
   
   }

}
