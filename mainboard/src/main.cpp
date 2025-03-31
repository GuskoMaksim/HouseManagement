#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "ManagerRX.h"
#include "ManagerSensor.h"
#include "ManagerSerial.h"
#include "SensorBME280.h"
#include "init.h"

ManagerRX<4> *rx;
ManagerSensor *M_Sensor;
ManagerSerial *M_Serial;

SensorModel *BME;

WiFiClient espClient;
PubSubClient client(espClient);

constexpr uint32_t refresh_interval_ms = 5000;
uint32_t timer_to_update_ms = refresh_interval_ms + 1;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1') {
    Serial.println("payload[0] == '1'");
  } else {
    Serial.println("payload[0] == '0'");
  }
}

void reconnect() {
  while (!client.connected()) {
    String ip = ipSer + String(ip4);
    client.setServer(ip.c_str(), 1883);
    Serial.println("Attempting MQTT connection... to " + ip);
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqttLogin.c_str(), mqttPassword.c_str())) {
      Serial.println("connected");
      client.publish("ESP32Client", "Connected");
      // client.subscribe("inTopic");
    } else {
      Serial.println("failed, rc=");
      Serial.println(client.state());
      Serial.println(" try again in 1 seconds");
      if (ip4 == 120) ip4 = 100;
      ip4 += 1;
      delay(1000);
    }
  }
}

void setup() {
  M_Serial = new ManagerSerial(115200);
  BME = new SensorBME280();
  M_Sensor = new ManagerSensor();
  rx = new ManagerRX<4>();
  M_Sensor->AddSensor(BME);
  M_Serial->AddManagerSensor(M_Sensor);
  setup_wifi();
  client.setServer((ipSer + String(ip4)).c_str(), 1883);
  client.setCallback(callback);
}

void loop() {
  rx->Update();
  if (!client.connected()) {
    Serial.println("--------------------------------Reconnect--------------------------------");
    reconnect();
    Serial.println("----------------------------END_____Reconnect----------------------------");
  } else if (millis() - timer_to_update_ms > refresh_interval_ms) {
    timer_to_update_ms = millis();
    Serial.println();
    Serial.println("------------------------------------------------------------");
    M_Sensor->Update();
    M_Serial->Update(true);
    // Radio
    {
      for (int i = 0; i < rx->storedDate_.getSize(); ++i) {
        String s = "";
        s += String(rx->storedDate_[i]->idDevice) + "/";
        switch (rx->storedDate_[i]->data.getSensorDataType()) {
          case SensorDataType::Temperature:
            s += "Temperature";
            break;
          case SensorDataType::Pressure:
            s += "Pressure";
            break;
          case SensorDataType::Humidity:
            s += "Humidity";
            break;
          default:
            s += String(static_cast<uint8_t>(rx->storedDate_[i]->data.getSensorDataType()));
            break;
        }
        Serial.print(s);
        Serial.print(" - ");
        Serial.println(String(rx->storedDate_[i]->data.getValue<float>()));
        client.publish(s.c_str(), String(rx->storedDate_[i]->data.getValue<float>()).c_str());
      }
    }
    // board
    {
      for (int i = 0; i < M_Sensor->GetDataFromSensors().getSize(); ++i) {
        String s = "mainboard/";
        switch (M_Sensor->GetDataFromSensors()[i].getSensorDataType()) {
          case SensorDataType::Temperature:
            s += "Temperature";
            break;
          case SensorDataType::Pressure:
            s += "Pressure";
            break;
          case SensorDataType::Humidity:
            s += "Humidity";
            break;
          default:
            s +=
                String(static_cast<uint8_t>(M_Sensor->GetDataFromSensors()[i].getSensorDataType()));
            break;
        }
        Serial.print(s);
        Serial.print(" - ");
        Serial.println(String(M_Sensor->GetDataFromSensors()[i].getValue<float>()).c_str());
        client.publish(s.c_str(), String().c_str());
      }
    }
    Serial.println("------------------------------------------------------------");
    Serial.println();
    client.loop();
  }
}
