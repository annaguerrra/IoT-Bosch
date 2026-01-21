#include <WiFi.h>

hw_timer_t *timer = NULL; // seta um ponteiro nulo do tipo hw_timer_t
int tempo = 0; // tempo começa como zero 

// IRAM_ATTR é um atributo de compilador usado em microcontroladores para forçar funções a serem armazenadas e executadas diretamente
// da Memória RAM de Instruções (IRAM), em vez da memória Flash, garantindo acesso ultrarrápido e sem latência

void IRAM_ATTR onTimer(){ 
  tempo ++;
}

void setup() {
  Serial.begin(9600); // inicialia o monitor serial
  timer = timerBegin(1000000); // preenche a variável timer com 1seg/1Hz
  timerAttachInterrupt(timer, &onTimer); // ativa o alarme do timer: a cada 1 segundo, o onTimer() vai ser executado
  timerAlarm(timer, 1000000, true, 0);
}

void loop() {
  Serial.println("Tempo" + String(tempo));

}

// struct hw_timer{
//   string nome;
//   int tempo;
//   int freq;
// }

// conectar no wifi
// - struct; - interrupção; - ponteiro;

// ntp network time protocol (pegar a hora)

// int tempo  = 80
// int *tempo = 80 -> ponteiro
// &tempo -> retorna o endereço da memória
