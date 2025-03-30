#include "ManagerSensor.h"

bool ManagerSensor::AddSensor(SensorModel* sensor) {
  if (sensor == nullptr) {
    return false;
  }
  for (int i = 0; i < listSensor_.getSize(); ++i) {
    if (listSensor_.get(i) == sensor) {
      return false;
    }
  }
  if (sensor->Init()) {
    listSensor_.add(sensor);
    return true;
  }
  return false;
}

void ManagerSensor::addToListAllDataFromSensor(SensorModel* sensor) {
  if (sensor == nullptr) {
    return;
  }
  for (uint8_t i = 0; i < sensor->getModuleInfo().countOfTypes; ++i) {
    listData_.add(sensor->getData(sensor->getModuleInfo().types[i]));
  }
}

void ManagerSensor::Update() {
  for (int i = 0; i < listSensor_.getSize(); ++i) {
    listSensor_.get(i)->Update();
  }
}

List<Variant>& ManagerSensor::GetDataFromSensors() {
  listData_.clear();
  for (int i = 0; i < listSensor_.getSize(); ++i) {
    addToListAllDataFromSensor(listSensor_.get(i));
  }
  return listData_;
}
