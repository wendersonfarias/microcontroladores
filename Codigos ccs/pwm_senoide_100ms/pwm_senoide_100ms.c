#include "C:\Users\wende\Desktop\MICRO\pwm_senoide_100ms\pwm_senoide_100ms.h"


int cont = 0;
int numero = 0, ton;

const unsigned int seno[80] = {0,0,1,2,3,5,7,9,12,14,18,21,
                  25,29,33,37,41,45,50,54,58,62,66,70,74,78,81,
                  81,81,85,87,90,92,94,96,97,98,99,99,98,97,96,94,92,
                  90,87,85,81,78,74,70,66,62,58,54,50,45,51,37,33,29,25,
                  25,21,18,14,12,9,7,5,3,2,1,0,0};
                  
#int_RTCC
void  RTCC_isr(void) 
{
   if(++cont >= 3 ){  // 409 * 3 = 1227 us -> 1227 * 73 =~ 90 ms
      numero = numero + 1;
      ton = seno[numero];
      set_pwm1_duty(ton);
      cont = 0;
      IF(numero > 73) numero = 0;
   }
}


void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8); //overflow a cada 409 us
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_16,255,1);
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_OFF);
   set_pwm1_duty(99);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   enable_interrupts(INT_RTCC);
   enable_interrupts(GLOBAL);
   // TODO: USER CODE!!

}
