#pragma once
#include <Arduino.h>

#include "Variant.hpp"

class Module {
 public:
  Module(Module&) = delete;
  Module(Module&&) = delete;
  Module& operator=(Module&) = delete;
  Module& operator=(Module&&) = delete;
  Module() = default;
  virtual ~Module() = default;
  virtual void Update() = 0;
  virtual bool Init() = 0;
};
