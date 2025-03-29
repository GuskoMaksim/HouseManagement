#pragma once

#include "SensorModel.h"

class SensorML1 : public SensorModel {
 private:
  const ModuleInfo m_moduleInfo = {1, SensorDataType::Light};
  int8_t m_pin;
  Variant m_light;
  Variant m_averageLight;

 public:
  SensorML1(int8_t pin, ValueType type = ValueType::Int32_t);
  Variant& getData(SensorDataType type) override;
  const ModuleInfo& getModuleInfo() const override;
  bool Init() override;
  void Update() override;
  ~SensorML1() = default;
};
