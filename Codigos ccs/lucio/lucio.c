#include "C:\Users\wende\Desktop\MICRO\lucio\lucio.h"


//#include "C:\Users\lucio\Desktop\pwm\teste\0.h"

int16 T=0, cont=0, Ton=0, Toff;
// T referenta ao periodo total, cont para conta ciclos entre
//um incremento e outro, Ton e Toff para controle do duty
//cicle do PWM

#int_RTCC
void  RTCC_isr(void){
   //define o periodo total em 10 segundos
   if(T<6250){
      T++;
      Toff= 1000 - Ton;
      if(cont<3){
         cont++;
      }
      else{
         Ton++;
         cont=0;
      }
      output_high(PIN_B2);
      delay_us(Ton);
      output_low(PIN_B2);
   }
   else{
      T=0;
      cont=0;
      Ton=0;
   }
}



void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_RTCC);
   enable_interrupts(GLOBAL);
   //set_timer0(99);

   // TODO: USER CODE!!
   while(TRUE){
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

   // TODO: USER CODE!!

}
