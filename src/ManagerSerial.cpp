#include "ManagerSerial.h"

#include "ManagerSensor.h"
#include "TimerModel.h"

ManagerSerial::ManagerSerial(const int speed) {
  Serial.begin(speed);
  Serial.println("Start");
}

void ManagerSerial::SendDebugDataToSerialPort() {
  if (timer_) {
    Serial.print(timer_->Get_data_time_().date_);
    Serial.print(".");
    Serial.print(timer_->Get_data_time_().month_);
    Serial.print(".");
    Serial.print(timer_->Get_data_time_().year_);
    Serial.println("");
    Serial.print(timer_->Get_data_time_().hour_);
    Serial.print(":");
    Serial.print(timer_->Get_data_time_().minute_);
    Serial.print(":");
    Serial.print(timer_->Get_data_time_().second_);
    Serial.println("");
  }
  if (data_) {
    for (int i = 0; i < data_->GetDataFromSensors().getSize(); ++i) {
      String s = "";
      switch (data_->GetDataFromSensors().get(i).getSensorDataType()) {
        case SensorDataType::Temperature:
          s += "Temperature";
          break;
        case SensorDataType::Pressure:
          s += "Pressure";
          break;
        case SensorDataType::Humidity:
          s += "Humidity";
          break;
        default:
          s += String(static_cast<uint8_t>(data_->GetDataFromSensors().get(i).getSensorDataType()));
          break;
      }
      s += " - " + String(data_->GetDataFromSensors().get(i).getValue<float>());
      Serial.print(s);
      Serial.println("");
    }
  }
  Serial.println("");
}

void ManagerSerial::Update(bool debug) {
  if (debug) {
    SendDebugDataToSerialPort();
  }
};
