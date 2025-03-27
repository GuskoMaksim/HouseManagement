#include "SensorMHz19B.h"

SensorMHz19B::SensorMHz19B(ValueType type, int8_t RX_MHZ, int8_t TX_MHZ)
    : m_Co2(type, SensorDataType::Co2), m_RX_MHZ(RX_MHZ), m_TX_MHZ(TX_MHZ) {};

bool SensorMHz19B::Init() {
  m_mhz19.begin(m_TX_MHZ, m_RX_MHZ);
  m_mhz19.setAutoCalibration(false);
  m_mhz19.getStatus();
  delay(2000);
  if (!(m_mhz19.getStatus() == 0)) {
    Serial.println("Error of INIT!");
    return false;
  } else {
    Update();
    m_averageCo2.setValue(m_Co2);
    Serial.println("MH-Z19B module added to the device!");
    return true;
  }
};

void SensorMHz19B::Update() { m_Co2.setValue(static_cast<int16_t>(m_mhz19.getPPM())); };

Variant& SensorMHz19B::getData(SensorDataType type) {
  switch (type) {
    case SensorDataType::Co2:
      m_averageCo2.setValue(
          static_cast<float>((m_averageCo2.getValue<float>() * 5.0f + m_Co2.getValue<float>())) /
          6.0f);
      return m_averageCo2;
      break;
    default:
      static_assert("ERROR of getData from MH-Z19B");
      break;
  };
  static_assert("ERROR of getData from MH-Z19B");
  return m_Co2;
};

const SensorMHz19B::ModuleInfo& SensorMHz19B::getModuleInfo() const { return m_moduleInfo; };
