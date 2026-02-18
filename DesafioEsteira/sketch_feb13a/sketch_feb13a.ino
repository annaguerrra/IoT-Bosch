#include <PubSubClient.h>
#include <WiFi.h>
#include "env.h"

WiFiClient espClient;
PubSubClient client(espClient);

const int pinIR = 32;
int lastState = HIGH;  

void WiFiEvent(WiFiEvent_t event){
  switch(event){

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("WiFi conectado!");
      attemptMqttConnection();
      break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("WiFi perdido!");
      WiFi.begin(ssid, password);
      break;
  }
}

boolean attemptMqttConnection() {

  String clientId = String(mqtt_client_id) + "_" + WiFi.macAddress();

  if (client.connect(
        clientId.c_str(),
        NULL,
        NULL,
        topico_status,
        0,
        true,
        "OFFLINE"
      )) {

    Serial.println("MQTT conectado!");
    client.publish(topico_status, "ONLINE", true);
    client.subscribe(topico_comando);
    return true;

  } else {
    Serial.print("Erro MQTT: ");
    Serial.println(client.state());
    return false;
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Mensagem recebida");
}

void setup() {

  Serial.begin(115200);

  pinMode(pinIR, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.onEvent(WiFiEvent);

  WiFi.begin(ssid, password);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected())
    attemptMqttConnection();

  client.loop();

  int sensorState = digitalRead(pinIR);

  if (sensorState != lastState) {

    lastState = sensorState;

    if(sensorState == LOW){
      digitalWrite(LED_BUILTIN, HIGH);
      client.publish(topico_status, "OBJETO_DETECTADO", true);
      Serial.println("Objeto detectado");
    }
    else{
      digitalWrite(LED_BUILTIN, LOW);
      client.publish(topico_status, "SEM_OBJETO", true);
      Serial.println("Sem objeto");
    }
  }

  delay(100);
}
