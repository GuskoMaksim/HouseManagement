#include "Variant.hpp"

#include "TypeTraits.hpp"

Variant::Variant() {}

template <typename T>
void Variant::setValue(T value, ValueType type) {
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
  typeOfValue_ = type;
}

void Variant::setValue(Variant& value) {
  typeOfValue_ = value.typeOfValue_;
  typeOfSensorData_ = value.typeOfSensorData_;
  setValue(value.value_, value.typeOfValue_);
}

void Variant::setValueType(const ValueType typeOfValue) { typeOfValue_ = typeOfValue; }

void Variant::setSensorDataType(const SensorDataType typeOfSensorData) {
  typeOfSensorData_ = typeOfSensorData;
}

template <typename T>
T Variant::getValue() const {
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

const ValueType& Variant::getValueType() const { return typeOfValue_; }

const SensorDataType& Variant::getSensorDataType() const { return typeOfSensorData_; }