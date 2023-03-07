#include "C:\Users\wende\Desktop\MICRO\pwm_delay\pwm_delay.h"


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

   while(TRUE){
      output_low(PIN_B2);
      delay_us(100);
      output_high(PIN_B2);
      delay_us(100);
   }

}
