#include <PubSubClient.h>
#include <WiFi.h>
#include "env.h"

WiFiClient espClient;
PubSubClient client(espClient);


#define WIFI_SSID "BTIA_SON5CT"
#define WIFI_PASS "IUVr4qSh8kQe"

const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_client_id = "francisco";
const char* topico_comando = "dta/infra";

const int mqtt_port = 8884;


const int pinStart = 32;
const int pinEnd = 35;

int statusSensorEnd = 0;
int statusSensorStart = 0;

int lastState = HIGH;

void WiFiEvent(WiFiEvent_t event){
  switch(event){
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("WiFi conectado!");  
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("WiFi perdido. Conectando novamente");
      break;
  }
}

boolean attemptMqttConnection() {
  String clientId = String(mqtt_client_id) + "_" + WiFi.macAddress();

  if (client.connect(
        clientId.c_str(),
        NULL,
        NULL,
        topico_comando,
        0,
        true,
        "OFFLINE"
      )) {

    Serial.println("MQTT conectado!");
    // var como valor do infra
    client.publish(topico_comando, "ONLINE", true);
    return true;

  } else {
    Serial.print("Erro MQTT: ");
    Serial.println(client.state());
    return false;
  }
}

void callback(char* topic, byte* payload, unsigned int length){

  int statusSensorStart = digitalRead(pinStart);
  int statusSensorEnd = digitalRead(pinEnd);

  if (statusSensorStart == LOW) { // Se objeto detectado (LOW é comum para detecção)
    Serial.println("comecei");
  }

  if (statusSensorEnd == LOW) { // Se objeto detectado (LOW é comum para detecção)
    Serial.println("termineii");
  }
}


void setup() {

  Serial.begin(115200);
  pinMode(pinOut, INPUT);
  pinMode(pinStart, INPUT);
  pinMode(pinEnd, INPUT);

  WiFi.onEvent(WiFiEvent);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected())
    attemptMqttConnection();

  client.loop();

  int sensorStateStart = digitalRead(pinStart);
  int sensorStateEnd = digitalRead(pinEnd);


  if (statusSensorStart == LOW) { // Se objeto detectado (LOW é comum para detecção)
    client.publish(topico_comando, "OBJETO_INICIO", true);
    Serial.println("Objeto no Inicio");
  }

  if (statusSensorEnd == LOW) {
    client.publish(topico_comando, "OBJETO_FIM", true);
    Serial.println("Objeto no Fim");
  }
}

