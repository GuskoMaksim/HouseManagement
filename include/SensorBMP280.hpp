#pragma once
#include <GyverBME280.h>

#include "SensorModel.hpp"

class SensorBMP280 : public SensorModel {
 private:
  uint8_t module_address_;          // Device address for communication
  const float mmColumn_ = 132.32f;  // Conversion factor into millimeters of mercury column
  const ModuleInfo moduleInfo_ = {2, SensorDataType::Temperature, SensorDataType::Pressure};
  Variant m_temperature;
  Variant m_averageTemperature;
  Variant m_pressure;
  Variant m_averagePressure;
  GyverBME280 BME280_;

 public:
  SensorBMP280(ValueType type = ValueType::Float, uint8_t module_address_ = 0x76);
  Variant& getData(SensorDataType type) override;
  const ModuleInfo& getModuleInfo() const override;
  bool Init() override;
  void Update() override;
  ~SensorBMP280() = default;
};