#include <PubSubClient.h>
#include <WiFi.h>
#include "env.h"

#define WIFI_SSID "anna"
#define WIFI_PASS "annna#01"

const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_client_id = "francisco";
const char* topico_comando = "dta/infra";
const int mqtt_port = 8883; 

WiFiClient espClient;
PubSubClient client(espClient);
hw_timer_t *timer = NULL;

const int pinStart = 32;
const int pinEnd = 35;

int statusSensorEnd = 0;
int statusSensorStart = 0;

bool isConnected = false;

volatile unsigned long timeCounter = 0;

void WiFiEvent(WiFiEvent_t event){
  switch(event){
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("WiFi conectado!");  
      attemptMqttConnection();
      break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("WiFi perdido!");
      WiFi.begin(WIFI_SSID, WIFI_PASS);
      break;
  }
}

void Connection(){
  if(!client.connected()){
    isConnected = false; 

    if(timeCounter > 5000){
      timeCounter = 0;
      if(attemptMqttConnection()) {
        timeCounter = 0;
      }
    } 
  } 
  else{
    isConnected = true;
  }
}

void IRAM_ATTR onTimer(){
  if(!isConnected){
    timeCounter++;
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
      )){

      Serial.println("MQTT conectado!");
      client.publish(topico_comando, "ONLINE", true);
      client.subscribe(topico_comando);
      return true;

  } else {
    Serial.print("Erro MQTT: ");
    Serial.println(client.state());
    return false;
  }
}

void callback(char* topic, byte* payload, unsigned int length){

  statusSensorStart = digitalRead(pinStart);
  statusSensorEnd = digitalRead(pinEnd);

  if (statusSensorStart == LOW) {
    Serial.println("comecei");
  }

  if (statusSensorEnd == LOW) {
    Serial.println("termineii");
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(pinStart, INPUT);
  pinMode(pinEnd, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.onEvent(WiFiEvent);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000, true, 0);   

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  Connection();

  if (!client.connected()){
    attemptMqttConnection();
  }

  client.loop();

  statusSensorStart = digitalRead(pinStart);
  statusSensorEnd = digitalRead(pinEnd);

  if (statusSensorStart == LOW) {
    client.publish(topico_comando, "OBJETO_INICIO", true);
    Serial.println("Objeto no Inicio");
  }

  if (statusSensorEnd == LOW) {
    client.publish(topico_comando, "OBJETO_FIM", true);
    Serial.println("Objeto no Fim");
  }

  delay(100);
}