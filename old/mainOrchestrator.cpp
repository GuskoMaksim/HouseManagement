// #define G433_SPEED 1000
// #include "ManagerRX.h"
//
// ManagerRX rx;
//
// void setup() {
//    Serial.begin(9600);
//}
//
// void loop() {
//    rx.Update();
//}

// #include <Gyver433.h>
// Gyver433_RX<2, 20> rx;
//
// void /*IRAM_ATTR*/ isr() {
//   rx.tickISR();
// }
//
// void setup() {
//   Serial.begin(9600);
//   attachInterrupt(0, isr, CHANGE);
// }
//
// void loop() {
//   if (rx.gotData()) {
//     char data[15];
//     if (rx.readData(data)) Serial.print(data);
//     else Serial.print("Data error");
//     Serial.print(", RSSI: ");
//     Serial.println(rx.getRSSI());
//   }
//   delay(50);
// }