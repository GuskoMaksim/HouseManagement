// #include <Arduino.h>
// //
// #include "DisplayLCD2004.h"
// #include "ManagerRX.h"
// #include "ManagerSensor.h"
// #include "ManagerSerial.h"
// #include "ManagerStorage.h"
// #include "SensorBMP280.h"
// #include "SensorMHz19B.h"
// #include "SensorMQ2.h"
// #include "TimerDS3231.h"

// //
// constexpr uint32_t refresh_interval_ms = 5000;
// uint32_t timer_to_update_ms = refresh_interval_ms + 1;
// //

// ManagerStorage *M_Storage;
// ManagerSensor *M_Sensor;
// ManagerSerial *M_Serial;
// SensorModel *BMP;
// SensorModel *MHZ;
// TimerModel *DS;
// DisplayLCD2004 *LCD;
// ManagerRX<4> *rx;
// //
// // bool h = false;
// //
// void setup() {
//     Serial.begin(9600);
//     Serial.println("Start");

//     pinMode(2, OUTPUT);
//     // pinMode(25, OUTPUT);
//     // pinMode(26, OUTPUT);
//     digitalWrite(2, HIGH);
//     // digitalWrite(25, HIGH);
//     // digitalWrite(26, HIGH);

//     // rx = new ManagerRX<4>();

//     DS = new TimerDS3231();
//     DS->Init();
//     DS->Update();

//     BMP = new SensorBMP280();

//     MHZ = new SensorMHz19B(ValueType::INT16_T, 17, 16);
//     //// MHZ = new SensorMHz19B(ValueType::INT16_T, 3, 1);

//     M_Sensor = new ManagerSensor();
//     M_Sensor->AddSensor(BMP);
//     M_Sensor->AddSensor(MHZ);
//     M_Sensor->Update();

//     M_Serial = new ManagerSerial();
//     M_Serial->AddManagerSensor(M_Sensor);
//     M_Serial->AddTimer(DS);
//     M_Serial->Update();

//     M_Storage = new ManagerStorage();
//     M_Storage->AddManagerSensor(M_Sensor);
//     M_Storage->AddTimer(DS);
//     M_Storage->Update();

//     LCD = new DisplayLCD2004();
//     LCD->Init();
//     LCD->AddManagerSensor(M_Sensor);
//     LCD->AddTimer(DS);
//     LCD->Update();
// };

// void loop() {
//     // rx->Update();
//     if (millis() - timer_to_update_ms > refresh_interval_ms) {
//         timer_to_update_ms = millis();
//         M_Sensor->Update();
//         DS->Update();
//         M_Serial->Update(true);
//         M_Storage->Update();
//         LCD->Update();
//         //   if (h == false) {
//         //       h = true;
//         //       digitalWrite(27, HIGH);
//         //       digitalWrite(14, HIGH);
//         //       digitalWrite(12, HIGH);
//         //   } else {
//         //       h = false;
//         //       digitalWrite(27, LOW);
//         //       digitalWrite(14, LOW);
//         //       digitalWrite(12, LOW);
//         //   }
//     }
// };
