//#include "C:\Users\wende\Desktop\MICRO\microcontroladores\Codigos ccs\serial_dth11\serial_dth11.h"
#include <16F877A.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout rese
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=serial_pc)

#use fast_io(B)
#define DHT11_PIN PIN_B4    // connection pin between DHT11 and mcu

//variaveis
short Time_out;
unsigned int8 T_byte1, T_byte2, Hu_byte1, Hu_byte2, testaSoma ;

void start_sinal(){
  output_drive(DHT11_PIN);    // Define o pino especificado para o modo de saída.
  output_low(DHT11_PIN);      // saída do pino como baixo
  delay_ms(25);
  output_high(DHT11_PIN);     // saída do pino como baixo
  delay_us(30);
  output_float(DHT11_PIN);    // configurar pino de conexão como entrada
}

short testa_resposta(){
  delay_us(40);
  if(!input(DHT11_PIN)){      // leia e teste se o pino de conexão está baixo
    delay_us(80);
    if(input(DHT11_PIN)){     // leia e teste se o pino de conexão está alto
      delay_us(50);
      return 1;
    }
  }
}

unsigned int8 leitor_dados(){
  unsigned int8 i, cont, _data = 0;   // cont usando para contar duracao do bit 1
  if(Time_out)
    break;
  for(i = 0; i < 8; i++){
          cont = 0;
          while(!input(DHT11_PIN)){           // aguardando o pino ser nivel alto
            cont++;
            if(cont> 100){
              Time_out = 1;
              break;
            }
            delay_us(1);
          }
          delay_us(30);
          if(!input(DHT11_PIN))
            bit_clear(_data, (7 - i));        // limpa bit (7 - i)
          else{
            bit_set(_data, (7 - i));          // Seta bit (7 - i)
            while(input(DHT11_PIN)){          // Aguarde até que o pino DHT11 fique baixo
              cont++;
              if(cont > 100){
              Time_out = 1;
              break;
            }
            delay_us(1);}
    }
  }
  return _data;
}

void main()
{
   int t1,t2,t3;
   int h1,h2,h3;

   //port_b_pullups(TRUE);
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
      Time_out = 0;
      start_sinal();
      
      if(testa_resposta()){                     // If there is a response from sensor
      Hu_byte1 =  leitor_dados();                 // read RH byte1
      Hu_byte2 =  leitor_dados();                 // read RH byte2
      T_byte1 =   leitor_dados();                  // read T byte1
      T_byte2 =   leitor_dados();                  // read T byte2
      testaSoma =  leitor_dados();                 // read checksum
      if(Time_out){                           // Se a leitura demorar muito
                             
        //fprintf(serial_pc, "Time out! \n\t");
      }else{
         if(testaSoma == ((Hu_Byte1 + Hu_Byte2 + T_Byte1 + T_Byte2) & 0xFF)){
            t1 = T_Byte1/10  ;
            t2 = T_Byte1%10  ;
            t3 = T_Byte2/10  ;
            h1 = Hu_Byte1/10 ;
            h2 = Hu_Byte1%10 ;
            h3 = Hu_Byte2/10 ;
            fprintf(serial_pc, "temperatura %u%u.%u \n\t", t1, t2,t3);  
            fprintf(serial_pc, "humidade %u%u.%u \n\t", h1, h2,h3);
         }
         else{
            
            //fprintf(serial_pc, "Checksum Error! \n\t");
         }
      }
   }
   else {
      //lcd_putc('\f');                          // LCD clear
      //lcd_gotoxy(3, 1);                        // Go to column 3 row 1
      //lcd_putc("No response");
      //lcd_gotoxy(1, 2);                        // Go to column 1 row 2
      //lcd_putc("from the sensor");
    }
    
   
    delay_ms(1500);
   }
}
