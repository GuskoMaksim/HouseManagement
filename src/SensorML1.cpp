#include "SensorML1.h"

SensorML1::SensorML1(int8_t pin, ValueType type)
    : m_pin(pin),
      m_light(type, SensorDataType::Light),
      m_averageLight(type, SensorDataType::Light) {};

bool SensorML1::Init() {
  Update();
  m_averageLight.setValue(m_light);
  return true;
};

void SensorML1::Update() {
  float res = (4095 - analogRead(m_pin)) / 2 + (4095 - analogRead(m_pin)) / 2 +
              (4095 - analogRead(m_pin)) / 2 + (4095 - analogRead(m_pin)) / 2;
  m_light.setValue(res / 4.0f);
};

Variant& SensorML1::getData(SensorDataType type) {
  switch (type) {
    case SensorDataType::Light:
      m_averageLight.setValue(
          static_cast<float>((m_light.getValue<float>() * 5.0f + m_light.getValue<float>())) /
          6.0f);

      return m_light;
      break;
    default:
      static_assert("ERROR of getData from ML1");
      break;
  };
  static_assert("ERROR of getData from ML1");
  return m_light;
}

const SensorML1::ModuleInfo& SensorML1::getModuleInfo() const { return m_moduleInfo; };