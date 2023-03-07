//#include "C:\Users\wende\Desktop\MICRO\dente_serra\dente_serra.h"

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



int16 cont=0;


#int_TIMER1
void  TIMER1_isr(void){

   cont=cont+10;
   
   // 10000/10 = 1000;
   
   if(cont >10000){
      
      cont = 0;
      
   }
   
   
   set_pwm1_duty(cont/10);
   set_pwm2_duty(cont/10);
   
   set_timer1(15536);
   
}

void main()
{

   set_timer1(15536); // faz que o timer comece a contar a parTir 15536 ate 65536
   //overflow a cada 10ms
   
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   
   
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1); //overflow a cada 13,1ms
   setup_timer_2(T2_DIV_BY_16,255,1); //overflow  a cada 332us
   
   
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   
   set_pwm1_duty(1023);
   set_pwm2_duty(1023);
   
   
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_TIMER2);
   enable_interrupts(GLOBAL);
   
   while(TRUE);
       
   

}
