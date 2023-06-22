#include <WiFi.h>         
#include <IOXhop_FirebaseESP32.h>       //importa biblioteca para esp32 se comunicar com firebase                  
#include <ArduinoJson.h>     
#include <LiquidCrystal_I2C.h>  
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display            

#define WIFI_SSID "wenderson"                   
#define WIFI_PASSWORD "123wender"         
#define FIREBASE_HOST "https://esp32-gerencia-senha-default-rtdb.firebaseio.com/"    
#define FIREBASE_AUTH "AIzaSyBbgVccojxAZm4htNQzN8FsWTuV7dBhQIA"   

void setup() {
  Serial.begin(115200);
  Serial.println();
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0,0);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print("Conectando ao wifi");
  lcd.print("Conectando " );
  lcd.setCursor(0,1);
  lcd.print("ao wifi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.pushString("/teste/teste15","wenderson");

}

void loop() {
  
//Exemplo da função Get


  Serial.println();
  Serial.println("teste");
  delay(500);
  
  

}
