#ifndef ENV_H
#define ENV_H
#define WIFI_SSID "iPhone de Patrick"
#define WIFI_PASS "quadrado1"
#define LED_PIN 22                                                             //led que já vem soldado na esp32 

const char* mqtt_server    = "broker.hivemq.com";
const char* mqtt_client_id = "esp32_alunx";                                    // <---- Coloca o seu nomezinho aqui
const char* topico_desafio = "desafio/impossivel";
const char* topico_id      = "desafio/id";
const char* topico_comando = "dta/infra";
const int   mqtt_port      =  1883;

#endif