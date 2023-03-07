
//#include "C:\Users\wende\Desktop\MICRO\pwm_dente_serra\pwm_dente_serra.h"

#include <16F628A.h>
#device adc=8
#FUSES NOWDT, HS, NOPUT, NOPROTECT, NOBROWNOUT, NOLVP, NOCPD RESERVED
#use delay(clock=4000000)

int16 ton=0, toff;
unsigned int16 cont;
int1 ordem = 0; //0 - crescente - 1 decrescente

void main()
{

   while(TRUE){
      // 1000 us -> 
      
      
         IF(ton == 225 && ordem ==0){  // 225us * 225 * 2 =~ 101 ms
            ordem = 1;
         }
         
         if(ton == 0 && ordem == 1){
            ordem = 0;
         }
     
         
         if(ordem == 1 ){
            ton--; 
         }else{
            ton++;
         }
         
         toff = 225-ton;
         
         
         output_high(PIN_A0);
         delay_us(ton);
         output_low(PIN_A0);
         delay_us(toff);
         
         
        }
   
   
   
   
      
   
   
   


}
