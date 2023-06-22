//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

//LiquidCrystal lcd(<pino RS>, <pino enable>, <pino D4>, <pino D5>, <pino D6>, <pino D7>)

LiquidCrystal lcd(23, 22,21, 19, 18, 5);

void setup() {
    
   Serial.begin(9600);
  //Define o número de colunas e linhas do LCD
  Serial.println("resetou!!");
  lcd.begin(16, 2);
   lcd.clear();
}

void loop() {


  lcd.setCursor(5,0);
  lcd.print("ola wenderson");
  lcd.setCursor(7,1);
  lcd.print("ola teste");

 
  

  

}
