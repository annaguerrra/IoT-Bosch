/**
 * @author    patrosque
 * @brief     Cliente MQTT Industrial para IoT (ESP32).
 * Implementa protocolo Pub/Sub com LWT (Last Will),
 * reconexão não-bloqueante e identidade única via MAC.
 * @version   2.1.1 
 * @date      2026-01-19
 * @history
 * v1.0.0 - 2026-01-10 - Implementação básica do conexão MQTT
 * v1.1.0 - 2026-01-12 - Adição comunicação string unidirecional
 * v1.2.1 - 2026-01-19 - Organização em pastas
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "env.h"

unsigned long tempo = 0;
bool isConnected = false;

const int pinStart = 32;
const int pinEnd = 23;

int statusSensorStart = 0;
int statusSensorEnd = 0;

int lastStateStart = true;
int lastStateEnd = true;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  
  Serial.begin(115200);
  pinMode(pinStart, INPUT_PULLUP);
  pinMode(pinEnd, INPUT_PULLUP);
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  configWifi();      
  configuraTimer(); 
}

void loop() {
  statusSensorStart = digitalRead(pinStart);
  statusSensorEnd = digitalRead(pinEnd);
  
  if(digitalRead(pinStart) != lastStateStart){
      // Serial.println("Final: " + String(digitalRead(pinEnd)));
      // Serial.println("Inicio: " + String(digitalRead(pinStart)));
      lastStateStart = statusSensorStart;
    while (digitalRead(pinStart) == 0) {
      client.publish(topico_comando, "OBJETO_INICIO",true);
      Serial.println("Objeto no Inicio");
      
    }
  }

  if(digitalRead(pinEnd) != lastStateEnd){
      Serial.println(digitalRead(pinEnd));
      Serial.println(digitalRead(pinStart));
      lastStateEnd = statusSensorEnd;
    while (digitalRead(pinEnd) == 0) {
      client.publish(topico_comando, "OBJETO_FIM", true);
      Serial.println("Objeto no Fim");
      delay(1000);
    }
  }
  taConectado();
}
