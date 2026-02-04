// PISCA PISCA LEDS QUE TROCAM DE SENTIDO


int leds[] = {2, 4, 16, 25, 26, 27};
int botao = 18;

volatile int flag = 0;
volatile int rodando = 0;
volatile int sentido = 1; 
volatile int tmax = 200; 
volatile int tempo = 0;

int posicao = 0;
int qleds = 6;

hw_timer_t *timer = NULL;

// ta apertado ou nao
void IRAM_ATTR funcaoboa() {
  flag = 1;
}

// se os leds estão piscando e o tempo aceso ainda nao acabou, diminui tempo aceso
void IRAM_ATTR onTimer() {
  if (rodando && tempo > 0) {
    tempo --;
  }
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < qleds; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  pinMode(botao, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(botao),
    funcaoboa,
    FALLING
  );

  timer = timerBegin(1000000);              // preenche a variável timer com 1seg/1Hz
  timerAttachInterrupt(timer, &onTimer);    // ativa o alarme do timer: a cada 1 segundo, o onTimer() vai ser executado
  timerAlarm(timer, 1000, true, 0);         // ticks e repetição

  Serial.println("a");
}

void loop() {

  // se apertado, desaperta
  if (flag) {
    flag = 0;
    Serial.println("botao");

  // se nao tá rodando, roda, reseta tempo, liga led
    if(!rodando){
      rodando = 1; 
      tempo = tmax;
      digitalWrite(leds[posicao], HIGH);
    }
    // inverte sentido do pisca pisca
    else{
      sentido *= -1; 
    }
  }

  // se rodando e acabou tempo do led aceso, passa p prox led e verificao
  if(rodando && tempo == 0){
    digitalWrite(leds[posicao], LOW);

    posicao += sentido;

    if(posicao >= qleds){
      posicao = 0;
    }
    if(posicao < 0){
      posicao = qleds - 1;
    }

    // acende o vizinho do que foi apagado e reseta tempo
    digitalWrite(leds[posicao], HIGH);
    tempo = tmax;
  }
}