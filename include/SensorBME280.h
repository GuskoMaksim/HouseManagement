#pragma once
#include <GyverBME280.h>

#include "SensorModel.h"

class SensorBME280 : public SensorModel {
 private:
  uint8_t m_moduleAddress;           // Device address for communication
  const float m_mmColumn = 132.32f;  // Conversion factor into millimeters of mercury column
  const ModuleInfo m_moduleInfo = {3, SensorDataType::Temperature, SensorDataType::Humidity,
                                   SensorDataType::Pressure};
  Variant m_temperature;
  Variant m_pressure;
  Variant m_humidity;
  Variant m_averageTemperature;
  Variant m_averagePressure;
  Variant m_averageHumidity;
  GyverBME280 m_BME280;

 public:
  SensorBME280(ValueType type = ValueType::Float, uint8_t module_address_ = 0x76);
  Variant& getData(SensorDataType type) override;
  const ModuleInfo& getModuleInfo() const override;
  bool Init() override;
  void Update() override;
  ~SensorBME280() = default;
};
