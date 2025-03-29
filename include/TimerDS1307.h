#pragma once
#include <Arduino.h>
#include <RtcDS1307.h>
#include <Wire.h>

#include "TimerModel.h"

class TimerDS1307 : public TimerModel {
 private:
  RtcDS1307<TwoWire> Rtc;
  RtcDateTime now;
  bool wasError();
  void SetUpTimeOnModule() override;

 public:
  TimerDS1307();
  void Update() override;
  bool Init() override;
};

// CONNECTIONS:
// DS1307 SDA --> SDA
// DS1307 SCL --> SCL
// DS1307 VCC --> 5v
// DS1307 GND --> GND
