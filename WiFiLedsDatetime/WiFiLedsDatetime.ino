// wiFi, Datetime e Leds

#include "time.h"
#include <WiFi.h>

hw_timer_t *timer = NULL;

int verde10 = 18;
int vermelho2 = 19;
bool connected = false; 

const char* ssid = "anna";
const char* password = "annna#01";

const char* servidor = "pool.ntp.org";
const long fuso = -10800;  // -3 * 3600;
const int verao = 0;


void IRAM_ATTR connected(){
  if(!connected){
    digitalWrite(verde10, !digitalRead(verde10));
    digitalWrite(vermelho2, LOW);
  } else {
    digitalWrite(verde10, LOW);
    digitalWrite(vermelho2, !digitalRead(vermelho2));
  }
}

void WiFiEvent(WiFiEvent_t event) {
  switch (event) {

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      timerAttachInterrupt(timer, &connected);
      timerAlarm(timer, 100000, true, 0);
      Serial.println("Conectado");
      break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      timerAttachInterrupt(timer, &connected);
      timerAlarm(timer, 500000, true, 0);
      Serial.println("Desconectado");
      WiFi.reconnect();
      break;
  }
}

void setup() {
  Serial.begin(9600);
  timer = timerBegin(1000000);

  configTime(fuso, verao, servidor);

  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, password);
  Serial.println("Inicializando conexão WiFi");

  pinMode(vermelho2, OUTPUT);
  pinMode(verde10, OUTPUT);
}

void loop() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Sem hora");
      return;
    }
    Serial.println(&timeinfo);
}
