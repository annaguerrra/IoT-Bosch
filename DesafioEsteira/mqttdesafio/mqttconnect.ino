#include <PubSubClient.h>

extern unsigned long tempo;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("MSG recebida no tópico: ");
  Serial.println(topic);
} 

boolean attemptMqttConnection() {

  String clientId = String(mqtt_client_id) + "_" + String(WiFi.macAddress());
  Serial.print("Tentando MQTT como: " + clientId + "... ");

  if (client.connect(clientId.c_str(), NULL, NULL, topico_comando, 0, true, "0")){
    Serial.println("CONECTADO!");
    client.subscribe(topico_comando);
    return true;
  } else {
    Serial.print("Falha. rc=");
    Serial.print(client.state());
    return false;
  }
}

void taConectado(){
  if (!client.connected()) {
    isConnected = false;
    if (tempo > 5000) {
      tempo = 0;
      if (attemptMqttConnection()) tempo = 0;
    }
  } else {
    isConnected = true;
    client.loop();
  }
}