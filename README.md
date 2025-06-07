📡 Documentação Técnica – Monitoramento de Enchentes com ESP32 e Node-RED
📝 Sumário
Descrição Geral

Arquitetura do Sistema

Componentes Utilizados

Funcionamento do Sistema

Fluxo de Dados e Lógica de Alerta

Instruções de Implementação

Dashboard e Visualização

Links Importantes

Autores

📘 Descrição Geral
Este projeto propõe um sistema inteligente de monitoramento de enchentes, capaz de coletar dados ambientais em tempo real por meio de sensores acoplados a um ESP32, que atua como nó de borda (Edge Computing). Os dados são enviados via MQTT para um broker, onde são processados e visualizados usando o Node-RED.

O objetivo é fornecer uma solução de baixo custo, flexível e intuitiva para detectar riscos de inundações e emitir alertas automáticos de forma visual e acessível.

🧩 Arquitetura do Sistema
plaintext
Copiar
Editar
[Sensores (Nível Água, Umidade, Chuva)]
           ↓
        [ESP32]
    ↳ Lógica de Alerta (local)
    ↳ Envio via MQTT
           ↓
      [Broker MQTT]
           ↓
     [Node-RED Dashboard]
    ↳ Visualização
    ↳ Gráficos/Alertas
🛠️ Componentes Utilizados
Hardware
Componente	Função
ESP32 DevKit C	Microcontrolador principal
Sensor HC-SR04	Medição de nível da água
Sensor de umidade solo	Leitura da umidade do terreno
Potenciômetro	Simulação da quantidade de chuva
LED	Alerta visual local
Protoboard e Jumpers	Conexões

Software
Arduino IDE

Node-RED (https://nodered.org)

Broker MQTT (HiveMQ, Mosquitto, etc.)

Bibliotecas Arduino
cpp
Copiar
Editar
WiFi.h
PubSubClient.h
ArduinoJson.h
⚙️ Funcionamento do Sistema
Sensores
HC-SR04: Mede distância (nível da água).

Sensor de Umidade: Mede umidade do solo (0–100%).

Potenciômetro: Simula volume de chuva.

ESP32
Faz leitura dos sensores periodicamente.

Aplica regras locais de alerta (ex: se nível da água > 10cm e umidade > 80%).

Envia os dados em JSON via MQTT.

Node-RED
Recebe e interpreta as mensagens MQTT.

Exibe os dados em tempo real.

Gera gráficos e alerta visual com LED virtual e status textual.

🧠 Fluxo de Dados e Lógica de Alerta
Exemplo de JSON enviado:
json
Copiar
Editar
{
  "nivel_agua_cm": 12.5,
  "umidade_solo": 87,
  "volume_chuva": 70,
  "alerta": true
}
Lógica básica no ESP32:
cpp
Copiar
Editar
if (nivel_agua > 10 && umidade > 80) {
  alerta = true;
  digitalWrite(ledPin, HIGH);
} else {
  alerta = false;
  digitalWrite(ledPin, LOW);
}
🧪 Instruções de Implementação
1. Montagem do Hardware
Sensor/Componente	Pino ESP32
HC-SR04 Trig	D13
HC-SR04 Echo	D14
Umidade A0	A34
Potenciômetro	A32
LED	D22 (via 220Ω)

2. Código no ESP32 (Arduino IDE)
Configure SSID e senha do Wi-Fi.

Configure o broker MQTT e tópicos.

Faça upload do código para o ESP32.

cpp
Copiar
Editar
const char* ssid = "SEU_SSID_WIFI";
const char* password = "SUA_SENHA";
const char* mqtt_broker = "broker.hivemq.com";
const char* mqtt_topic = "sensor/monitoramento_enchente";
3. Node-RED
Instale o node-red-dashboard:

Menu → Manage Palette → Install → node-red-dashboard

Configure os nós:

mqtt in → Tópico: sensor/monitoramento_enchente

function → Interpretação do JSON

ui_gauge / ui_chart → Visualização

ui_text / ui_led → Alertas

📊 Dashboard e Visualização
Indicadores visuais para:

Nível da água (cm)

Umidade do solo (%)

Volume de chuva (%)

🔗 Links Importantes
💻 Projeto Wokwi: 

📺 Demonstração em Vídeo: 

👥 Autor
- Enzo Galhardo | RM561001
