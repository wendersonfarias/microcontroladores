#define GPIO_BOTAO 5
#define TEMPO_DEBOUNCE 10 //ms
 
int contador_acionamentos = 0;
unsigned long timestamp_ultimo_acionamento = 0;
 
/* Função ISR (chamada quando há geração da
interrupção) */
void IRAM_ATTR funcao_ISR()
  {
  /* Conta acionamentos do botão considerando debounce */
  if ( (millis() - timestamp_ultimo_acionamento) >= TEMPO_DEBOUNCE )
  {
      contador_acionamentos++;
      timestamp_ultimo_acionamento = millis();
  }
}
 
 
void setup()
{
    Serial.begin(115200);
     
    /* Configura o GPIO do botão como entrada
    e configura interrupção externa no modo
    RISING para ele.
    */
    pinMode(GPIO_BOTAO, INPUT);
    attachInterrupt(GPIO_BOTAO, funcao_ISR, RISING);
}
 
void loop()
{
  Serial.print("Acionamentos do botao: ");
  Serial.println(contador_acionamentos);
  
}
