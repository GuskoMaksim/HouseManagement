#pragma once
#include <DHT.h>

#include "SensorModel.h"

class SensorDHTGroup : public SensorModel {
 private:
  const ModuleInfo moduleInfo_ = {2, SensorDataType::Temperature, SensorDataType::Humidity};
  Variant temperature_;
  Variant humidity_;
  DHT dht;

 public:
  SensorDHTGroup(uint8_t module_type, ValueType type = ValueType::Float, uint8_t module_pin = 2);
  bool Init() override;
  void Update() override;
  Variant& getData(SensorDataType type) override;
  const ModuleInfo& getModuleInfo() const override;
  ~SensorDHTGroup() = default;
};
