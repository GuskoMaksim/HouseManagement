#include <Arduino.h>

#include "ManagerRX.h"
#include "ManagerSensor.h"
#include "ManagerSerial.h"
#include "SensorBME280.h"

ManagerRX<4> *rx;
ManagerSensor *M_Sensor;
ManagerSerial *M_Serial;

SensorModel *BME;

constexpr uint32_t refresh_interval_ms = 5000;
uint32_t timer_to_update_ms = refresh_interval_ms + 1;

void setup() {
  Serial.begin(115200);
  BME = new SensorBME280();
  M_Sensor = new ManagerSensor();
  M_Serial = new ManagerSerial();
  rx = new ManagerRX<4>();
  M_Sensor->AddSensor(BME);
  M_Serial->AddManagerSensor(M_Sensor);
  Serial.begin(115200);
}
void loop() {
  rx->Update();
  if (millis() - timer_to_update_ms > refresh_interval_ms) {
    timer_to_update_ms = millis();
    Serial.println("------------------------------------------------------------");
    M_Sensor->Update();
    M_Serial->Update(true);
    for (int i = 0; i < rx->storedDate_.getSize(); ++i) {
      Serial.print(String(rx->storedDate_[i]->idDevice));
      Serial.print("-");
      Serial.print(String(static_cast<uint8_t>(rx->storedDate_[i]->data.getSensorDataType())));
      Serial.print("-");
      Serial.println(String(rx->storedDate_[i]->data.getValue<float>()));
    }
    Serial.println("------------------------------------------------------------");
    Serial.println();
  }
}
