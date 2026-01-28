int led1 = 2;
int led2 = 4;
int led3 = 16;
int led4 = 25;
int led5 = 26;
int led6 = 27;
int botao = 18;

int fim = 6;
int flag = 0;          
int pisca = 0;
int leds[6] = {led1, led2, led3, led4, led5, led6};

void IRAM_ATTR funcao(){
  if(flag != 1 && flag != 2){
    flag = 1;
  }
  else{
    if(!digitalRead(botao)){
      flag = 2;
    }
  }
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(botao, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(botao),
    funcao,
    FALLING
  );

}

void loop() {
    if(flag == 1){
      for(int i = pisca; i <= 6; i++){
        pisca = i;
        digitalWrite(leds[i], HIGH);
        delay(50);
        digitalWrite(leds[i], LOW);
        pisca ++;
      }
    }
    if(flag == 2){
      pisca = 6;
      for(int i = pisca; i >= 0; i --){
        pisca = i;
        digitalWrite(leds[i], HIGH);
        delay(50);
        digitalWrite(leds[i], LOW);
        pisca--;
      }
      flag = 0;
    }
  }

  if(flag == 1){
    fim = 6;
  }
  else{
    fim = 0;
  }
  for(int i = pisca; i<= )
