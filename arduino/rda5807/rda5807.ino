/*
   Test and validation of RDA5807 on ESP32 board.
    
   ATTENTION:  
   Please, avoid using the computer connected to the mains during testing. Used just the battery of your computer. 
   This sketch was tested on ATmega328 based board. If you are not using a ATmega328, please check the pins of your board. 

  | RDA5807    | Function              |ESP LOLIN32 WEMOS (GPIO) |
  |-----------| ----------------------|-------------------------|
  | SDA/SDIO  |   SDIO                |   21 (SDA / GPIO21)     |
  | CLK/CLOCK |   SCLK                |   22 (SCL / GPIO22)     |


   By Ricardo Lima Caratti, 2020.
*/

#include <RDA5807.h>

// I2C bus pin on ESP32
#define ESP32_I2C_SDA 21
#define ESP32_I2C_SCL 22

#define MAX_DELAY_RDS 40   // 40ms - polling method

long rds_elapsed = millis();

RDA5807 rx;

char *rdsMsg;
char *stationName;
char *rdsTime;

void checkRDS()
{
  if (rx.getRdsReady())
  {
     if ( (rdsMsg = rx.getRdsText2A()) != NULL) 
        Serial.println(rdsMsg);
     else if ( (stationName = rx.getRdsText0A()) != NULL)
        Serial.println(stationName);
     else if ( (rdsTime = rx.getRdsTime()) != NULL )
        Serial.println(rdsTime);
  }
}

void showRds()
{
  if ( rx.getRdsReady() )
    checkRDS();
}


void showHelp()
{
  Serial.println("Digite U para aumentar e D para diminuir a frequência");
  Serial.println("Digite S ou s para buscar a estação Up ou Down");
  Serial.println("Digite + ou - para aumentar ou diminuir o volume");
  Serial.println("Digite 0 para mostrar o status atual");
  Serial.println("digite ? para ajuda!.");
  Serial.println("==================================================");
  delay(1000);
}

// Show current frequency
void showStatus()
{
  char aux[80];
  sprintf(aux,"\nVocê está sintonizado em %u MHz | RSSI: %3.3u dbUv | Vol: %2.2u | %s ",rx.getFrequency(), rx.getRssi(), rx.getVolume(), (rx.isStereo()) ? "Yes" : "No" );
  Serial.print(aux);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial) ;

    // The line below may be necessary to setup I2C pins on ESP32
    Wire.begin(ESP32_I2C_SDA, ESP32_I2C_SCL);
    
    rx.setup();

    rx.setVolume(6);

    delay(500);

    // Select a station with RDS service in your place
    Serial.print("\nEstacao 99.9MHz");
    rx.setFrequency(9990); // It is the frequency you want to select in MHz multiplied by 100.

    // Enables SDR
    rx.setRDS(true);

    showHelp();
    showStatus();
 
}

void loop()
{
  if ((millis() - rds_elapsed) > MAX_DELAY_RDS ) {
    if ( rx.getRdsReady() )  checkRDS();
    rds_elapsed = millis();
  }
  
  if (Serial.available() > 0)
  {
    char key = Serial.read();
    switch (key)
    {
    case '+':
      rx.setVolumeUp();
      break;
    case '-':
      rx.setVolumeDown();
      break;
    case 'U':
    case 'u':
      rx.setFrequencyUp();
      break;
    case 'D':
    case 'd':
      rx.setFrequencyDown();
      break;
    case 'S':
      rx.seek(RDA_SEEK_WRAP, RDA_SEEK_UP);
      break;
    case 's':
      rx.seek(RDA_SEEK_WRAP, RDA_SEEK_DOWN);
      break;
    case '0':
      showStatus();
      break;
    case '?':
      showHelp();
      break;
    default:
      break;
    }
    delay(200);
    showStatus();
  } 
  delay(5);
}
