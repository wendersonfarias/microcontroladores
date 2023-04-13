//#include "C:\Users\wende\Desktop\MICRO\microcontroladores\Codigos ccs\miniteste_q2\miniteste_q2.h"
/*#include <16F877A.h>
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

int16 led1, led2, led3, led4, led5;

#int_RTCC
void  RTCC_isr(void) 
{
   
   
   if(++led3 > 109 ){
      output_toggle(PIN_D5);
      led3 = 0;
   }
   
   if(++led4 > 71){
      output_toggle(PIN_D4);
      led4 = 0;
   }
   
   if(++led5 > 40){
      output_toggle(PIN_D3);
      led5 = 0;
   }
   
   set_timer0(get_timer1()+12);
   
   
}


#int_TIMER1
void  TIMER1_isr(void) 
{  
   
   
   if(++led1 >50 /2){
      output_toggle(PIN_D7);
      led1 = 0;
   }
   
   if(++led2 > 250 /2 ){
      output_toggle(PIN_D6);
      led2 = 0;
   }
   
  set_timer1(get_timer1() + 15536 );

}



void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2); //overflow a cada 102 us
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);  //overflow a cada 13,1 ms
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_RTCC);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   
   //overlow a cada 100us
   
   set_timer0(6);    // preencho timer0 para contar 6 a 255]
   
   //overflow a cada 10ms
   set_timer1(15536 ); // preencho o timer1 para contar 15536 ate 65536 

   while(TRUE);

}*/

#include <16F877A.h>
#device adc = 8
#FUSES NOWDT, HS, NOPUT, NOPROTECT, NODEBUG, BROWNOUT, NOLVP, NOCPD, NOWRT, NOWRT
#use delay(clock = 20MHz)

unsigned int16 cont1 = 0, cont2 = 0, cont3 = 0;

#int_TIMER0
void TIMER0_isr(void){
   if(++cont1 >= 394/2)  { cont1 = 0; output_toggle(pin_B0) ; } 
   if(++cont2 >= 1927/2) {cont2 = 0;output_toggle(pin_B1); }
   if(++cont3 >= 822/2) {cont3 = 0; output_toggle(pin_B2); }
}

void main(){
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_1); // overflow 51,2 us
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   //disable_interrupts(GLOBAL);
   
   while(true);
}
