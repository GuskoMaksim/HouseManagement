#include "SensorBME280.h"

SensorBME280::SensorBME280(ValueType type, uint8_t module_address)
    : m_moduleAddress(module_address),
      m_temperature(type, SensorDataType::Temperature),
      m_pressure(type, SensorDataType::Pressure),
      m_humidity(type, SensorDataType::Humidity),
      m_averageTemperature(type, SensorDataType::Temperature),
      m_averagePressure(type, SensorDataType::Pressure),
      m_averageHumidity(type, SensorDataType::Humidity),
      m_BME280() {};

bool SensorBME280::Init() {
  if (!m_BME280.begin(m_moduleAddress)) {
    Serial.println("Error of INIT!");
    return false;
  } else {
    do {
      Update();
    } while ((m_temperature.getValue<float>() < 1.0f && m_temperature.getValue<float>() > -1.0f));
    m_averageTemperature.setValue(m_temperature);
    m_averagePressure.setValue(m_pressure);
    m_averageHumidity.setValue(m_humidity);
    Serial.println("SensorBME280::Init()");
    return true;
  }
};

void SensorBME280::Update() {
  m_temperature.setValue(static_cast<float>(m_BME280.readTemperature()));
  m_pressure.setValue(static_cast<float>(m_BME280.readPressure() / m_mmColumn));
  m_humidity.setValue(static_cast<float>(m_BME280.readHumidity()));
};

Variant& SensorBME280::getData(SensorDataType type) {
  switch (type) {
    case SensorDataType::Temperature:
      m_averageTemperature.setValue(
          static_cast<float>(
              (m_averageTemperature.getValue<float>() * 7.0f + m_temperature.getValue<float>())) /
          8.0f);
      return m_averageTemperature;
      break;
    case SensorDataType::Pressure:
      m_averagePressure.setValue(static_cast<float>((m_averagePressure.getValue<float>() * 7.0f +
                                                     m_pressure.getValue<float>())) /
                                 8.0f);
      return m_averagePressure;
      break;
    case SensorDataType::Humidity:
      m_averageHumidity.setValue(static_cast<float>((m_averageHumidity.getValue<float>() * 7.0f +
                                                     m_humidity.getValue<float>())) /
                                 8.0f);
      return m_averageHumidity;
      break;
    default:
      static_assert("ERROR of getData from BME280");
      break;
  };
  static_assert("ERROR of getData from BME280");
  return m_temperature;
};

const SensorBME280::ModuleInfo& SensorBME280::getModuleInfo() const { return m_moduleInfo; };
