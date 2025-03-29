#pragma once
#include <SD.h>
#include <SPI.h>

#include "ManagerSensor.h"
#include "Module.h"
#include "TimerModel.h"

class ManagerStorage {
 private:
  File dataFile_;
  TimerModel *timer_ = nullptr;
  ManagerSensor *data_ = nullptr;
  const uint8_t chipSelect = 5;
  void PrintData(Variant var);

 public:
  ManagerStorage();
  void AddTimer(TimerModel *timer);
  void AddManagerSensor(ManagerSensor *data);
  void Update();
  ~ManagerStorage() = default;
};
