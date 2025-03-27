#include "SensorBMP280.h"

SensorBMP280::SensorBMP280(ValueType type, uint8_t module_address)
    : module_address_(module_address),
      m_temperature(type, SensorDataType::Temperature),
      m_averageTemperature(type, SensorDataType::Temperature),
      m_pressure(type, SensorDataType::Pressure),
      m_averagePressure(type, SensorDataType::Pressure),
      BME280_() {}

bool SensorBMP280::Init() {
  if (!BME280_.begin(module_address_)) {
    Serial.println("Error of INIT!");
    return false;
  } else {
    do {
      Update();
    } while ((m_temperature.getValue<float>() < 1.0f && m_temperature.getValue<float>() > -1.0f));
    m_averageTemperature.setValue(m_temperature);
    m_averagePressure.setValue(m_pressure);
    Serial.println("BME280 module added to the device!");
    return true;
  }
};

void SensorBMP280::Update() {
  m_temperature.setValue(BME280_.readTemperature());
  m_pressure.setValue(BME280_.readPressure() / mmColumn_);
};

Variant& SensorBMP280::getData(SensorDataType type) {
  switch (type) {
    case SensorDataType::Temperature:
      m_averageTemperature.setValue(
          static_cast<float>(
              (m_averageTemperature.getValue<float>() * 5.0f + m_temperature.getValue<float>())) /
          6.0f);
      return m_averageTemperature;
      break;
    case SensorDataType::Pressure:
      m_averagePressure.setValue(static_cast<float>((m_averagePressure.getValue<float>() * 5.0f +
                                                     m_pressure.getValue<float>())) /
                                 6.0f);
      return m_averagePressure;
      break;
    default:
      static_assert("ERROR of getData from BME280");
      break;
  };
  static_assert("ERROR of getData from BME280");
  return m_temperature;
};

const SensorBMP280::ModuleInfo& SensorBMP280::getModuleInfo() const { return moduleInfo_; };
