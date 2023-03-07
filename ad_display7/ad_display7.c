//#include "C:\Users\wende\Desktop\MICRO\ad_display7\ad_display7.h"

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

//declaracao variaveis globais
int8 milhar, centena, dezena, unidade;
int cont;
int16 poten1, poten2;

int8 numero[11] = {
         0X3F,//D 0 B*00111111
         0X06,//D 1 B*00000110
         0X5B,//D 2 B*01011011
         0X4F,//D 3 B*01001111
         0X66,//D 4 B*01100110
         0X6D,//D 5 B*01101101
         0X7D,//D 6 B*01111101
         0X07,//D 7 B*00000111
         0X7F,//D 8 B*01111111
         0X6F,//D 9 B*01101111
         };
         

#int_RTCC
void  RTCC_isr(void) 
{
   if(++cont > 4) cont = 0;
   
   if(cont == 1){
   //ligo os pinos a2 a a4
      output_high(PIN_A2);
      output_low(PIN_A3);
      output_low(PIN_A4);
      output_low(PIN_A5);
      
      output_d(numero[milhar]);
   }
   if(cont == 2){
      output_low(PIN_A2);
      output_high(PIN_A3);
      output_low(PIN_A4);
      output_low(PIN_A5);
      output_d(numero[centena]);
   }
   if(cont == 3){
      output_low(PIN_A2);
      output_low(PIN_A3);
      output_high(PIN_A4);
      output_low(PIN_A5);
      output_d(numero[dezena]);
   }
   if(cont == 4){
     output_low(PIN_A2);
      output_low(PIN_A3);
      output_low(PIN_A4);
      output_high(PIN_A5);

      output_d(numero[unidade]);
   }
   
   
   set_pwm1_duty(poten1);
   set_pwm2_duty(poten2);
   
}



void main()
{
   int16 aux;
   
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   
   setup_adc(ADC_CLOCK_DIV_16); // recebe os valores a cada 3,2 us
   
   //seta portas adc an0, an1, an3
   setup_adc_ports(AN0_AN1_AN3);
   
   //config timers
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_16,255,1);;//overflow a cada 819us
   
   //configuracoes pwm
   setup_ccp1(CCP_PWM); //ativa o ccp1
   setup_ccp2(CCP_PWM);
   
   //seta os pwm na metade do ciclo 
   set_pwm1_duty(512);
   set_pwm2_duty(512);
   
   
   //interrupcoes -usando timer 1;
   
   enable_interrupts(INT_RTCC);
   enable_interrupts(GLOBAL);
   
   //seleciona canal 0
   set_adc_channel(0);
   delay_us(20);
   
   output_low(pin_a5);
   
   while(TRUE){
      set_adc_channel(0);
      delay_us(20);
   
      poten1 = read_adc();
     
      set_adc_channel(1);
      delay_us(20);
      poten2 = read_adc();
      
      milhar = poten1 / 1000;  //resultado inteiro 999/1000 = 0
      
      aux = poten1 % 1000;  //recebe o resto da div 1023 % 1000 = 23
      
      centena = aux / 100;  // resultado inteiro 23 / 100 = 0
      
      aux = aux % 100;     //recebe o resto da div 23 % 100 = 23
      
      dezena = aux / 10;   // resultado inteiro 23 / 10 = 2
      
      aux = aux % 10;     //recebe o resto da div 23 % 10 = 3
      
      unidade = aux;     //recebe o resto da divisao interia da dezena
      
      
     
      
     
      
      
   }

}
