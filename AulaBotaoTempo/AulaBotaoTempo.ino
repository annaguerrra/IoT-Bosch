// AUMENTA TEMPO CONFORME APERTA BOTAO

volatile int  botao = 0;
int pinBotao = 26;
int flagbotao = 0;

hw_timer_t *timer = NULL; 
int tempo = 0;

// se botao nao foi apertado, aperta e reseta tempo 
void IRAM_ATTR funcaoBoa(){
  if(flagbotao != 1){   // 
    flagbotao = 1;
    tempo = 200;
  }

}

// se apertado e tempo maior que zero, diminui tempo
void IRAM_ATTR onTimer(){ 
  if(flagbotao == 1){
    if(tempo > 0){
      tempo--;
    } else{
      flagbotao = 0;
    }
  }
}

void setup(){
  Serial.begin(115200);
  pinMode(pinBotao, INPUT_PULLUP);

  timer = timerBegin(1000000); 
  timerAttachInterrupt(timer, &onTimer); 
  timerAlarm(timer, 1000000, true, 0);

  attachInterrupt(
    digitalPinToInterrupt(pinBotao),
    funcaoBoa,
    FALLING             // Modo
  );
}

void loop(){
  Serial.println(botao);
  Serial.print("Tempo" + String(tempo));
  delay(500);
}
