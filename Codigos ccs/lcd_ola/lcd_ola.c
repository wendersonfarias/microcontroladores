//#include "C:\Users\wende\Desktop\MICRO\microcontroladores\Codigos ccs\lcd_ola\lcd_ola.h"
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


#ifndef lcd_enable
   #define lcd_enable       pin_d1      // pino enable do LCD
   #define lcd_rs         pin_d0      // pino rs do LCD
   //#define lcd_rw      pin_e2      // pino rw do LCD
   #define lcd_d4         pin_c5      // pino de dados d4 do LCD
   #define lcd_d5         pin_c4      // pino de dados d5 do LCD
   #define lcd_d6         pin_d3      // pino de dados d6 do LCD
   #define lcd_d7         pin_d2      // pino de dados d7 do LCD
#endif
#include<mod_lcd.c>

void main()
{

   int16 leitura;
   float graus;
   
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
   
   lcd_ini();
   delay_ms(100);

   while(TRUE){
   
      
         leitura = read_adc();
      
      
      
      graus = leitura * 0.489;
      
      printf(lcd_escreve,"\f leitura \r\n");
      printf(lcd_escreve,"   %f  ", graus);
      lcd_pos_xy(30,2);
      
      delay_ms(200);
   }

}
