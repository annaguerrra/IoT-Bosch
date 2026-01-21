#include <WiFi.h>

const char* ssid = "iPhone de Patrick";
const char* password = "quadrado1";

void WiFiEvent(WiFiEvent_t event){
  switch(event){
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("Conectado");
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("Desconectado");
      WiFi.reconnect();
      break;

  }
}

void setup() {
  Serial.begin(9600);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, password);
  Serial.println("Inicializando conexão WiFi");
}

void loop() {
  

}
