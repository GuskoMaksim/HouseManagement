// #include <Arduino.h>
// #include <SoftwareSerial.h>
// SoftwareSerial SIM800(2, 3);        // 8 - RX Arduino (TX SIM800L), 9 - TX Arduino (RX SIM800L)
// void setup() {
//   SIM800.begin(9600);               // Скорость обмена данными с модемом
//   Serial.begin(9600);               // Скорость обмена данными с компьютером
//   Serial.println("Start!");
//   SIM800.println("AT");
// }
//
// void loop() {
//   if (SIM800.available())           // Ожидаем прихода данных (ответа) от модема...
//     Serial.write(SIM800.read());    // ...и выводим их в Serial
//   if (Serial.available())           // Ожидаем команды по Serial...
//     SIM800.write(Serial.read());    // ...и отправляем полученную команду модему
// }

// #include <Arduino.h>
//
// #include "ManagerSensor.h"
// #include "ManagerSerial.h"
// #include "SensorBMP280.h"
// #include "ManagerTX.h"
// #include "SensorMQ2.h"
//
//
// constexpr uint32_t refresh_interval_ms = 10000;
// uint32_t timer_to_update_ms = refresh_interval_ms + 1;
//
// constexpr uint32_t  refresh_send_ms = 10000;
// uint32_t send_update_ms =  refresh_send_ms + 1;
//
// ManagerSerial *MSerial;
// ManagerSensor *Manager;
// SensorModel *Sensor2;
// SensorModel *SensorBMP;
// ManagerTX *Tx;
//
//
// void setup() {
//     pinMode(4, OUTPUT);
//     digitalWrite(4, HIGH); // зажечь светодиод превышения
//     MSerial = new ManagerSerial();
//     Manager = new ManagerSensor();
//     Sensor2 = new SensorMQ2();
//     SensorBMP = new SensorBMP280();
//     Tx = new ManagerTX();
//     Manager->AddSensor(Sensor2);
//     Manager->AddSensor(SensorBMP);
//     MSerial->AddManagerSensor(Manager);
//     Tx->AddManagerSensor(Manager);
//     Manager->Update();
// }
//
// void loop() {
//     if (millis() - timer_to_update_ms > refresh_interval_ms) {
//         timer_to_update_ms = millis();
//         Manager->Update();
//         MSerial->Update(true);
//     }
//     if (millis() - send_update_ms > refresh_send_ms) {
//         send_update_ms = millis();
//         Tx->Update();
//     }
// };

// #include <Arduino.h>
//
// #include <List.hpp>
//
// #include "ManagerSensor.h"
// #include "SensorBME280.h"
// constexpr uint32_t refresh_interval_ms = 1000;
// uint32_t timer_to_update_ms;
// ManagerSensor m;
// SensorBME280 *q;
// void setup() {
//   Serial.begin(9600);
//   Serial.println("Start");
//   q = new SensorBME280();
//   m.AddSensor(q);
// };
//
// void loop() {
//   if (millis() - timer_to_update_ms > refresh_interval_ms) {
//     timer_to_update_ms = millis();
//     m.Update();
//     for (int i = 0; i < m.GetDataFromSensors().getSize(); i++) {
//       Serial.print(static_cast<uint8_t>(m.GetDataFromSensors().getValue(i).typeOfSensorData));
//       Serial.print(" - ");
//       Serial.print(m.GetDataFromSensors().getValue(i).getValue<uint16_t>());
//       Serial.print("   ");
//     }
//     Serial.println("");
//   }
// };

// #include <Arduino.h>

// constexpr uint32_t refresh_interval_ms = 1000;
// uint32_t timer_to_update_ms;

// void setup() {
//     Serial.begin(9600);
//     Serial.println("Start");
// };

// void loop() {
//     if (millis() - timer_to_update_ms > refresh_interval_ms) {
//         timer_to_update_ms = millis();
//     }
// };