#pragma once

#include <Arduino.h>

#include "Types.hpp"

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
  template <typename T>
  void setValue(T value, ValueType type);
  void setValue(Variant& value);
  void setValueType(const ValueType typeOfValue);
  void setSensorDataType(const SensorDataType typeOfSensorData);
  template <typename T>
  T getValue() const;
  const ValueType& getValueType() const;
  const SensorDataType& getSensorDataType() const;
};
