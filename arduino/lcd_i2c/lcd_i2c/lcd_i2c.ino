#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

byte pinosLinhas[] = { 33, 25,26,27 };
byte pinosColunas[] = { 19, 18, 14 };
char teclas[4][3] = { '1', '2', '3',
                       '4', '5', '6',
                       '7', '8', '9',
                       '*', '0', '#'};
                       
Keypad teclado = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 3);

const int buttonPin = 23;
void setup()
{
  
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  for (int i = 0; i <= 15; i++) {
    lcd.setCursor(0, 0);
    lcd.print("Carregando...");
    lcd.setCursor(i, 1);
    lcd.print("*");
    delay(200);
    lcd.clear();
  }

  montaTelaMenu();

}


void loop()
{
 

  char tecla_pressionada = teclado.getKey();
  if(tecla_pressionada){
    lcd.setCursor(0,1);
    lcd.print("tecla: " );
    lcd.print(tecla_pressionada );
    Serial.println("Tecla: ");
    Serial.println(tecla_pressionada);
  }
}

void montaTelaMenu() {
  Serial.println("menu()");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digite a senha");
  
}
