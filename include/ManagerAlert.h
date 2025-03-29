#pragma once
#include "ManagerSensor.h"

class ManagerAlert {
 private:
  ManagerSensor *M_Sensor_;

 public:
  ManagerAlert(ManagerSensor *M_Sensor);
  ~ManagerAlert() = default;
};
