#include "SensorDHTGroup.h"

SensorDHTGroup::SensorDHTGroup(uint8_t module_type, ValueType type, uint8_t module_pin)
    : temperature_(type, SensorDataType::Temperature),
      humidity_(type, SensorDataType::Humidity),
      dht(module_type, module_pin) {};

bool SensorDHTGroup::Init() {
  dht.begin();
  Serial.println("DHT module added to the device!");
  return true;
};

void SensorDHTGroup::Update() {
  temperature_.setValue(static_cast<float>(dht.readTemperature()));
  humidity_.setValue(static_cast<float>(dht.readHumidity()));
};

Variant& SensorDHTGroup::getData(SensorDataType type) {
  switch (type) {
    case SensorDataType::Temperature:
      return temperature_;
      break;
    case SensorDataType::Humidity:
      return humidity_;
      break;
    default:
      static_assert("ERROR of getData from DHT");
      break;
  };
  static_assert("ERROR of getData from DHT");
  return temperature_;
};

const SensorDHTGroup::ModuleInfo& SensorDHTGroup::getModuleInfo() const { return moduleInfo_; };
