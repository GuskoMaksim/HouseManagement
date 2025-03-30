#include "Variant.h"

Variant::Variant() {}

void Variant::setValue(Variant& value) {
  typeOfValue_ = value.typeOfValue_;
  typeOfSensorData_ = value.typeOfSensorData_;
  if (typeOfValue_ == ValueType::Bool)
    value_.bool_value = value.value_.bool_value;
  else if (typeOfValue_ == ValueType::Float)
    value_.float_value = value.value_.float_value;
  else if (typeOfValue_ == ValueType::Int32_t)
    value_.int32_value = value.value_.int32_value;
}

void Variant::setValueType(const ValueType typeOfValue) {
  //
  typeOfValue_ = typeOfValue;
}

void Variant::setSensorDataType(const SensorDataType typeOfSensorData) {
  typeOfSensorData_ = typeOfSensorData;
}

const ValueType& Variant::getValueType() const {
  //
  return typeOfValue_;
}

const SensorDataType& Variant::getSensorDataType() const {
  //
  return typeOfSensorData_;
}
