#include <Arduino.h>

#include "ManagerSensor.h"
#include "ManagerSerial.h"
#include "ManagerTX.h"
#include "SensorBMP280.h"

constexpr uint32_t refresh_interval_ms = 5000;
uint32_t timer_to_update_ms = refresh_interval_ms + 1;

constexpr uint32_t refresh_interval_send_ms = 10000;
uint32_t timer_to_send_update_ms = refresh_interval_send_ms + 1;

ManagerSensor *M_Sensor;
ManagerSerial *M_Serial;
ManagerTX *M_TX;

SensorModel *BMP;

void setup() {
  Serial.begin(9600);

  BMP = new SensorBMP280();
  M_Sensor = new ManagerSensor();
  M_Serial = new ManagerSerial();
  M_TX = new ManagerTX();

  M_Sensor->AddSensor(BMP);
  M_TX->AddManagerSensor(M_Sensor);
  M_Serial->AddManagerSensor(M_Sensor);

  auto update = [&]() {
    delay(1000);
    M_Sensor->Update();
  };
  update();
  update();

  M_Serial->Update(true);
}

void loop() {
  if (millis() - timer_to_update_ms > refresh_interval_ms) {
    timer_to_update_ms = millis();
    M_Sensor->Update();
    M_Serial->Update(true);
  }
  if (millis() - timer_to_send_update_ms > refresh_interval_send_ms) {
    timer_to_send_update_ms = millis();
    M_TX->Update();
  }
}
