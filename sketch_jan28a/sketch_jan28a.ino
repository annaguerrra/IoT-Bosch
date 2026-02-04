int led1 = 2;
int led2 = 4;
int led3 = 16;
int led4 = 25;
int led5 = 26;
int led6 = 27;
int botao = 18;

volatile int sentido = 1; 
volatile int estado = 0;
volatile int posicao = 0;
int tempo = 200;
int leds[6] = {led1, led2, led3, led4, led5, led6};

hw_timer_t *timer = NULL; 


void IRAM_ATTR funcao(){
//   if(flag != 1 && flag != 2){
//     flag = 1;
//   }
//   else{
//     if(!digitalRead(botao)){
//       flag = 2;
//     }
//   }
  if(estado == 1) {
    if (tempo > 0){
      tempo --;
    }
    else {
      estado = 0;
      if (!digitalRead(botao)){
        sentido *= -1;
        estado = 1;
        tempo = 200;
      }
    }
  }
}

void setup() {
  Serial.begin(9600);

  timer = timerBegin(1000000);
  timerAlarm(timer, 1000, true, 0);
  timerAttachInterrupt(timer, &funcao); 
  
  for(int i = 0; i <= 6; i++){
    pinMode(leds[i], OUTPUT);
  }
  pinMode(botao, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(botao),
    funcao,
    FALLING
  );

}

void loop() {
  //   if(flag == 1){
  //     for(int i = pisca; i <= 6; i++){
  //       pisca = i;
  //       digitalWrite(leds[i], HIGH);
  //       delay(50);
  //       digitalWrite(leds[i], LOW);
  //       pisca ++;
  //     }
  //   }
  //   if(flag == 2){
  //     pisca = 6;
  //     for(int i = pisca; i >= 0; i --){
  //       pisca = i;
  //       digitalWrite(leds[i], HIGH);
  //       delay(50);
  //       digitalWrite(leds[i], LOW);
  //       pisca--;
  //     }
  //     flag = 0;
  //   }
  if(posicao >= 6){
    posicao = 0;
  }
  if(posicao < 0){
    posicao = 0;
  }

  
  //if(estado == 1 && tempo > 0){
        digitalWrite(leds[posicao], HIGH);
        delay(200);
   // }
  //if(tempo == 0){
    digitalWrite(leds[posicao], LOW);
    posicao += sentido;

   // posicao += sentido;
 // }

  
}

