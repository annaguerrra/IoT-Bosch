#include <PubSubClient.h>
#include <WiFi.h>
#include "env.h"

WiFiClient espClient;
hw_timer_t *timer = NULL;
PubSubClient client();

const int ldr = 33;
const int led = 16;
const int limiar = 2500;

unsigned long time = 0; 
int valorLDR = 0;
bool luz;
bool conectado;

void WiFiEvent(WiFiEvent_t event){
  switch(event){
    case ARDUINO_EVENT
  }
}



void IRAM_ATTR onTimer(){
  if(!isConnected) time++;
}

boolean attemptMqttConnection(){
  String clientId = String(mqtt_client_id) + "_" + String(WiFi.macAddress());

  if(client.connect(
      clientId.c_str(),
      NULL,
      NULL,
      topico_status,
      0,
      true, 
      "OFFLINE"
  )){
    return true;
    Serial.println("Conectado.")
    client.publish(topico_status, "luz", true);
    client.subscribe(topico_comando);
  } 
  else{
    Serial.print(client.state());
    return false;
  }
}

void isConnected(){
  if(!client.connected(){
    conectado = false; 
    if(time > 5000){
      tempo = 0;
      if(attemptMqttConnection()) tempo = 0;
    } 
    else{
      conectado = true;
      client.loop();
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length){
  // String msg = "";
  // for( unsigned int i = 0; i < length; i++){
  //   msg += (char)payload[i];
  // }
  valorLDR = analogRead(ldr);
  Serial.println(valorLDR);
}

void setup() {
  Serial.begin(115200);
  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000, true, 0);
}

void loop() {
  isConnected();

  // valorLDR = analogRead(ldr);
  if (valorLDR > limiar) { // Se a luz for baixa (escuridão)
    digitalWrite(led, LOW);
    luz = true;
  } else {
    digitalWrite(led, HIGH);
    luz = false;
  }

  // Serial.println(valorLDR);
  Serial.println(luz);
}
