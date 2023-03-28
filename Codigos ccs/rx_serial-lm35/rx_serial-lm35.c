//#include "C:\Users\wende\Desktop\MICRO\microcontroladores\Codigos ccs\rx_serial-lm35\rx_serial-lm35.h"
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
#use rs232(baud=1200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=sensor)

int1 flagI = 0, flagF =0,flagM = 0,flagT = 0;
int8 valor;
int8 recebido;

#int_RDA
void  RDA_isr(void) 
{
   recebido = getc();
   if(recebido == 'i'){
      flagI = 1;
   }
   if(recebido == 'f'  ){
       flagF = 1;
   }
   if(recebido == 'm' ){
       flagM = 1;
   }
   if(recebido == 't' ){
       flagT = 1;
   }
   if (flagI == 1 && flagF == 1 && flagM == 1 && flagT == 1 ){
       valor = recebido;
       output_toggle(PIN_D1);
       flagI = 0;
       flagF = 0;
       flagM = 0;
       flagT = 0;
     
   }
}



void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

   while(TRUE){
      //valor = make16(parteBaixa,parteAlta);
      
      fprintf(sensor, "%u \n", valor);
   }

}
