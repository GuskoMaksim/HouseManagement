#pragma once

class TimerModel;
class ManagerSensor;

class ManagerSerial {
 private:
  TimerModel *timer_ = nullptr;
  ManagerSensor *data_ = nullptr;
  void SendDebugDataToSerialPort();

 public:
  ManagerSerial();
  ~ManagerSerial();
  void AddTimer(TimerModel *timer) { timer_ = timer; }
  void AddManagerSensor(ManagerSensor *data) { data_ = data; }
  void Update(bool debug = false);
  // void printData(Variant var);
};
