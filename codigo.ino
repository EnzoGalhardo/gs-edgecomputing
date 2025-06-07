#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h> 

#define triggerPin 13
#define echoPin 14
#define distanciaMaxima 200

#define soloPin 34
#define chuvaPin 32

#define nivelMaximoAgua 180
#define nivelMaximoSolo 2500
#define nivelMaximoChuva 2000

const char* ssid = "Wokwi-GUEST"; 
const char* password = ""; 

const char* mqtt_broker = "broker.hivemq.com"; 
const int mqtt_port = 1883;
const char* mqtt_client_id = "Enzo-Monitoramente"; 
const char* mqtt_topic_publish = "globalsolution/monitoramento";  

WiFiClient espClient;
PubSubClient client(espClient);

// Medir Distancia
long measureDistanceCm() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distanceCm = duration / 58;

  if (distanceCm == 0 || distanceCm > distanciaMaxima) {
    return distanciaMaxima;
  }
  return distanceCm;
}

// Conectar WI-FI
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// Reconectar ao Broker
void reconnect_mqtt() {
  // Loop até estar conectado
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT Broker...");
    // Tenta conectar
    if (client.connect(mqtt_client_id)) {
      Serial.println("conectado");
    } else {
      Serial.print("falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

// Envia dados via MQTT
void sendDataViaMQTT(float nivel_agua, int umidade_solo, int volume_chuva) {
  if (!client.connected()) {
    reconnect_mqtt();
  }

  StaticJsonDocument<256> doc; 
  doc["nivel_agua"] = nivel_agua;
  doc["umidade_solo"] = umidade_solo;
  doc["volume_chuva"] = volume_chuva;

  String jsonString;
  serializeJson(doc, jsonString); 

  Serial.print("Publicando dados MQTT no topico '");
  Serial.print(mqtt_topic_publish);
  Serial.print("': ");
  Serial.println(jsonString);

  // Publica no tópico MQTT
  if (client.publish(mqtt_topic_publish, jsonString.c_str())) {
    Serial.println("Dados MQTT publicados com sucesso!");
  } else {
    Serial.println("Falha ao publicar dados MQTT.");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("Serial Aberta!");
  

  setup_wifi();
  client.setServer(mqtt_broker, mqtt_port);
  reconnect_mqtt(); 
}

void loop() {
  // Garante que o MQTT esteja sempre conectado
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop();

  unsigned int distancia_cm = measureDistanceCm();
  float nivel_agua_cm = (distancia_cm >= distanciaMaxima) ? 0 : (distanciaMaxima - distancia_cm);

  int umidadeSolo = analogRead(soloPin);
  int volumeChuva = analogRead(chuvaPin);

  // Lógica de Alerta 
  bool riscoEnchente = false;

  if (nivel_agua_cm >= nivelMaximoAgua) {
    Serial.println("    -> Nivel de agua critico!");
    riscoEnchente = true;
  }

  if (umidadeSolo >= nivelMaximoSolo && volumeChuva >= nivelMaximoChuva) {
    Serial.println("    -> Solo saturado e chuva forte!");
    riscoEnchente = true;
  }

  if (riscoEnchente) {
    Serial.println("!!! ALERTA DE ENCHENTE !!!");
  }

  sendDataViaMQTT(nivel_agua_cm, umidadeSolo, volumeChuva);
  Serial.println("----------------------------------------------------------");
  delay(5000); 
}