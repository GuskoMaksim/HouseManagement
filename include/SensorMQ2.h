#pragma once

#include <TroykaMQ.h>

#include "SensorModel.h"

class SensorMQ2 : public SensorModel {
 private:
  const ModuleInfo moduleInfo_ = {4, SensorDataType::LPG, SensorDataType::Methane,
                                  SensorDataType::Smoke, SensorDataType::Hydrogen};
  const ValueType type;
  MQ2 mq2;
  Variant LPG_;
  Variant Methane_;
  Variant Smoke_;
  Variant Hydrogen_;

 public:
  SensorMQ2(uint8_t pinA = 2);
  Variant& getData(SensorDataType type) override;
  const ModuleInfo& getModuleInfo() const override;
  bool Init() override;
  void Update() override;
  ~SensorMQ2() = default;
};
