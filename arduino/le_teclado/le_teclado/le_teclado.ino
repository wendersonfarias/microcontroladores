const int coluna1 = 23;
const int coluna2 = 35;
const int coluna3 = 34;

const int linha1 = 27;
const int linha2 = 26;
const int linha3 = 25;
const int linha4 = 33;

char caractere = 'w';

void setup() {
  pinMode(coluna1, OUTPUT);
  pinMode(coluna2, OUTPUT);
  pinMode(coluna3, OUTPUT);

  pinMode(linha1, INPUT_PULLUP);
  pinMode(linha2, INPUT_PULLUP);
  pinMode(linha3, INPUT_PULLUP);
  pinMode(linha4, INPUT_PULLUP);
  
  Serial.begin(9600);

  while(!Serial);

  Serial.println("Lendo Teclado!");
  
}

void loop() {


    
  
    caractere = le_teclado(1500);

    if(caractere != 'w'){
      Serial.println("Tecla pressionada: " +(String)caractere);
    }else{
      Serial.println("nenhuma tecla pressionada!");
    }
  
    
  

}

char le_teclado(int segundos){
  int tempo;
  char leitura = 'P';

  

  while(tempo < segundos || leitura== 'P'){
      //coluna 1 
      digitalWrite(coluna1, LOW);
      digitalWrite(coluna1, HIGH);
      digitalWrite(coluna1, HIGH);
      delay(20);
    
      if(digitalRead(linha1) == LOW ){
        while(digitalRead(linha1) == LOW){
          leitura = '1';
        }
      }
      if(digitalRead(linha2) == LOW ){
        while(digitalRead(linha2) == LOW){
          leitura = '4';
        }
      }
      if(digitalRead(linha3) == LOW ){
        while(digitalRead(linha3) == LOW){
          leitura = '7';
        }
      }
    
      if(digitalRead(linha4) == LOW ){
        while(digitalRead(linha4) == LOW){
          leitura = '*';
        }
      }
      //coluna 3
      digitalWrite(coluna1, HIGH);
      digitalWrite(coluna1, LOW);
      digitalWrite(coluna1, HIGH);
      delay(20);
    
       if(digitalRead(linha1) == LOW ){
        while(digitalRead(linha1) == LOW){
          leitura = '2';
        }
      }
      if(digitalRead(linha2) == LOW ){
        while(digitalRead(linha2) == LOW){
          leitura = '5';
        }
      }
      if(digitalRead(linha3) == LOW ){
        while(digitalRead(linha3) == LOW){
          leitura = '8';
        }
      }
    
      if(digitalRead(linha4) == LOW ){
        while(digitalRead(linha4) == LOW){
          leitura = '0';
        }
      }
    
      //coluna 3
      digitalWrite(coluna1, HIGH);
      digitalWrite(coluna1, HIGH);
      digitalWrite(coluna1, LOW);
      delay(20);
    
       if(digitalRead(linha1) == LOW ){
        while(digitalRead(linha1) == LOW){
          leitura = '3';
        }
      }
      if(digitalRead(linha2) == LOW ){
        while(digitalRead(linha2) == LOW){
          leitura = '6';
        }
      }
      if(digitalRead(linha3) == LOW ){
        while(digitalRead(linha3) == LOW){
          leitura = '9';
        }
      }
    
      if(digitalRead(linha4) == LOW ){
        while(digitalRead(linha4) == LOW){
          leitura = '#';
        }
      }

      delay(5);
      tempo = tempo + 5;
  
  }
  
  return leitura;
}
