#pragma once
#include <Arduino.h>
#include <RtcDS1302.h>
#include <ThreeWire.h>

#include "TimerModel.h"

class TimerDS1302 : public TimerModel {
 private:
  ThreeWire myWire;
  RtcDS1302<ThreeWire> Rtc;
  RtcDateTime now;
  void SetUpTimeOnModule() override;

 public:
  TimerDS1302(uint8_t DAT = 4, uint8_t CLK = 5, uint8_t RST = 2);
  void Update() override;
  bool Init() override;
};

// CONNECTIONS :
// DS1302 DAT/IO --> 4
// DS1302 CLK/SCLK --> 5
// DS1302 RST/CE --> 2
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND
