#pragma once

#include <stdlib.h>

#include "TypeTraits.h"
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
      : typeOfValue_(type), typeOfSensorData_(typeOfSensorData) {
    value_.bool_value = false;
    value_.float_value = 0.0f;
    value_.int32_value = 0;
  };

  Variant(const Variant& variant)
      : value_(variant.value_),
        typeOfValue_(variant.typeOfValue_),
        typeOfSensorData_(variant.typeOfSensorData_) {}

  template <typename T>
  void setValue(T value) {
    if constexpr (is_same<T, bool>::value) {
      value_.bool_value = value;
      typeOfValue_ = ValueType::Bool;
    } else if constexpr (is_same<T, float>::value) {
      value_.float_value = value;
      typeOfValue_ = ValueType::Float;
    } else if constexpr (is_same<T, int32_t>::value) {
      value_.int32_value = value;
      typeOfValue_ = ValueType::Int32_t;
    } else {
      static_assert("Unsupported type for setValue");
    }
  }

  void setValue(Variant& value);
  void setValueType(const ValueType typeOfValue);
  void setSensorDataType(const SensorDataType typeOfSensorData);

  template <typename T>
  T getValue() const {
    if (typeOfValue_ == ValueType::Bool && is_same<T, bool>::value) {
      return value_.bool_value;
    } else if (typeOfValue_ == ValueType::Float && is_same<T, float>::value) {
      return value_.float_value;
    } else if (typeOfValue_ == ValueType::Int32_t && is_same<T, int32_t>::value) {
      return value_.int32_value;
    } else {
      Serial.println("ERROR: Incorrect type requested from Variant");
      return T();
    }
  }

  const ValueType& getValueType() const;
  const SensorDataType& getSensorDataType() const;
};
