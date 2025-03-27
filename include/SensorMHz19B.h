#pragma once

#include "MHZ19_uart.h"
#include "SensorModel.h"

class SensorMHz19B : public SensorModel {
 private:
  const ModuleInfo m_moduleInfo = {1, SensorDataType::Co2};
  Variant m_Co2;
  Variant m_averageCo2;
  int8_t m_RX_MHZ;
  int8_t m_TX_MHZ;
  MHZ19_uart m_mhz19;

 public:
  SensorMHz19B(ValueType type = ValueType::Int32_t, int8_t RX_MHZ = 2, int8_t TX_MHZ = 3);
  Variant& getData(SensorDataType type) override;
  const ModuleInfo& getModuleInfo() const override;
  bool Init() override;
  void Update() override;
  ~SensorMHz19B() = default;
};
