#pragma once
#include <Arduino.h>
#include <RtcDS3231.h>
#include <Wire.h>

#include "TimerModel.h"

class TimerDS3231 : public TimerModel {
 private:
  RtcDS3231<TwoWire> Rtc;
  RtcDateTime now;
  bool wasError();
  void SetUpTimeOnModule() override;

 public:
  TimerDS3231();
  void Update() override;
  bool Init() override;
};

// CONNECTIONS:
// DS3231 SDA --> SDA
// DS3231 SCL --> SCL
// DS3231 VCC --> 3.3v or 5v
// DS3231 GND --> GND
