# Monitoramento de Enchentes: Sistema Inteligente com ESP32 e Node-RED

## 📘 Descrição do Projeto

Este projeto propõe um sistema de **monitoramento de enchentes** utilizando um microcontrolador **ESP32**, sensores ambientais e uma interface de visualização desenvolvida com **Node-RED**. O sistema opera com base em conceitos de **Edge Computing** e **IoT**, coletando e analisando dados como:

- **Nível da água** (sensor ultrassônico)
- **Umidade do solo**
- **Volume de chuva** (simulado com potenciômetro)

Os dados são enviados via **protocolo MQTT** para um broker e exibidos em tempo real através de um **dashboard interativo no Node-RED**.

---

## 🎯 Objetivos

- **Detecção Precoce:** Antecipar situações de risco de enchentes.
- **Monitoramento em Tempo Real:** Acompanhamento contínuo de dados ambientais.
- **Visualização Intuitiva:** Dados claros e acessíveis via dashboard.
- **Alertas Automatizados:** Notificações visuais e LED de alerta.
- **Aplicação de IoT e Edge Computing:** Solução moderna e eficiente para problemas reais.

---

## 🔧 Funcionalidades

- Medição de nível da água (HC-SR04)
- Medição de umidade do solo
- Simulação do volume de chuva (potenciômetro)
- Processamento local (ESP32 com lógica embarcada)
- Comunicação MQTT com broker público
- Visualização no Node-RED com gráficos, indicadores e histórico
- Alertas visuais com LED no hardware e avisos no dashboard
- Saída serial para debug e monitoramento

---

## 💻 Requisitos do Sistema

### Hardware

- ✅ ESP32 DevKit C (ou equivalente)
- ✅ Sensor Ultrassônico HC-SR04
- ✅ Sensor de Umidade do Solo
- ✅ Potenciômetro (simulação de chuva)
- ✅ Protoboard e jumpers
- ✅ Fonte de energia (USB ou externa)

### Software

- **Arduino IDE**
- **Node-RED** (https://nodered.org ou https://flowfuse.com)
- **Broker MQTT** (ex.: HiveMQ ou Mosquitto)

### Bibliotecas Arduino IDE

- `WiFi.h`
- `PubSubClient.h`
- `ArduinoJson.h`

### Paletas Node-RED

- `node-red-dashboard`

---

## 🛠️ Instruções de Uso

### 1. Montagem do Hardware

| Componente               | Conexão no ESP32                                 |
|--------------------------|--------------------------------------------------|
| HC-SR04 (ultrassônico)   | VCC → 5V ou 3.3V<br>GND → GND<br>Trig → D13<br>Echo → D14 |
| Umidade do Solo          | VCC → 3.3V<br>GND → GND<br>A0 → A34              |
| Potenciômetro (chuva)    | VCC → 3.3V<br>GND → GND<br>Pino Central → A32    |
| LED (alerta)             | Ânodo → D22 (com resistor de 220Ω)<br>Cátodo → GND |

---

### 2. Código no Arduino IDE

1. Abra o Arduino IDE.
2. Insira o código do projeto.
3. Configuração do Node-RED
-Acesse http://localhost:1880
-Importe o flows para o node-red
4. Teste e Monitoramento
Simulador (Wokwi): use sliders para alterar os sensores

### 👨‍💻 Autor
-Enzo Galhardo RM 561001
