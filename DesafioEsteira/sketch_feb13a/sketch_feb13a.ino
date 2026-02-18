#include <PubSubClient.h>
#include <WiFi.h>
#include "env.h"

WiFiClient espClient;
hw_timer_t *timer = NULL;
PubSubClient client();

const int pinIR = 32; 
unsigned long time = 0; 
bool conectado;

// conexão WiFi
void WiFiEvent(WiFiEvent_t event){
  switch(event){
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.printl("WiFi conectado!");
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("WiFi perdido. Conectando novamente");
      break;
  }
}

// timer usado na conexão 
void IRAM_ATTR onTimer(){
  if(!isConnected) time++;
}

// conectando no CLP - não terminado
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
      time = 0;
      if(attemptMqttConnection()) time = 0;
    } 
    else{
      conectado = true;
      client.loop();
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length){
  int statusSensor = digitalRead(pinIR);

  if(statusSensor == LOW){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Objeto detectado");
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(pinIR, INPUT);
  pinMode(LED_BUILTINT);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000, true, 0);
}

void loop(){
  isConnected();
}




