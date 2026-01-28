// TIME

#include "time.h"
#include <WiFi.h>

int verde10 = 16;
int vermelho2 = 2; 

// config led verde 10Hz
const int canal10 = 0;
const int freq10 = 10;
const int resolucao = 8;

// config led vermelho 2Hz

const int canal2 = 1;
const int freq2 = 2;

const char* ssid = "iPhone de Patrick";
const char* password = "quadrado1";

const char* servidor = "pool.ntp.org";
const long fuso = -10800; // -3 * 3600;
const int verao = 0;

void WiFiEvent(WiFiEvent_t event){
  switch(event){
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      
      ledcAttachPin(verde10, canal10);
      // digitalWrite(verde10, 1);
      // digitalWrite(vermelho2, 0);
      Serial.println("Conectado");
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      
      ledcAttachPin(vermelho2, canal2);
      // digitalWrite(vermelho2, 1);
      // digitalWrite(verde10, 0);
      Serial.println("Desconectado");
      WiFi.reconnect();
      break;

  }
}

void setup() {
  // conectar na internet
  Serial.begin(9600);
  configTime(fuso, verao, servidor);
  
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, password);
  Serial.println("Inicializando conexão WiFi");
  ledcSetup(canal10, freq10, resolucao);
  ledcSetup(canal2, freq2);
}

void loop() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Sem hora");
    return;
  }
  Serial.println(&timeinfo);
}
