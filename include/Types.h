#pragma once
#include <Arduino.h>

enum class SensorDataType : uint8_t {
  Temperature = 0,
  Pressure,
  Humidity,
  Co2,
  LPG,
  Methane,
  Smoke,
  Hydrogen,
  Light,
};

enum class ValueType : uint8_t { Bool = 0, Float, Int32_t };

enum class MessageType : uint8_t { Data = 1, Signal = 2 };
