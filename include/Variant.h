#pragma once

#include <stdlib.h>

#include "Types.h"

union Value {
  bool bool_value;
  float float_value;
  int32_t int32_value;
};

class Variant {
 private:
  Value value_;
  ValueType typeOfValue_;
  SensorDataType typeOfSensorData_;

 public:
  Variant();
  Variant(ValueType type, SensorDataType typeOfSensorData)
      : typeOfValue_(type), typeOfSensorData_(typeOfSensorData) {};
  Variant(const Variant& variant)
      : value_(variant.value_),
        typeOfValue_(variant.typeOfValue_),
        typeOfSensorData_(variant.typeOfSensorData_) {}

  template <typename T>
  void setValue(T value);
  void setValue(Variant& value);
  void setValueType(const ValueType typeOfValue);
  void setSensorDataType(const SensorDataType typeOfSensorData);
  template <typename T>
  T getValue() const;
  const ValueType& getValueType() const;
  const SensorDataType& getSensorDataType() const;
};
