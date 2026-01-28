volatile int  botao = 0;

void setup(){
    Serial.begin(9600);

     attachInterrupt(
            digitalPinToInterrupt(Pin),
            funcaoBoa,
            FALLING             // Modo
     );
}

void IRAM_ATTR funcaoBoa(){
          botao++;
}

void loop(){
   Serial.print(botao);
}