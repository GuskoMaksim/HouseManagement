#include "ManagerStorage.h"

ManagerStorage::ManagerStorage() {
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  }
  Serial.println("Card open!");
};

void ManagerStorage::AddTimer(TimerModel *timer) { timer_ = timer; };

void ManagerStorage::AddManagerSensor(ManagerSensor *data) { data_ = data; };

void ManagerStorage::PrintData(Variant var) {
  switch (var.getValueType()) {
    case ValueType::Bool:
      dataFile_.print(var.getValue<bool>());
      break;
    case ValueType::Float:
      dataFile_.print(var.getValue<float>());
      break;
    case ValueType::Int32_t:
      dataFile_.print(var.getValue<int32_t>());
      break;
  }
};

void ManagerStorage::Update() {
#ifdef ESP32
  if (timer_ != nullptr) {
    dataFile_ = SD.open("/" + (String)timer_->Get_data_time_().date_ + "." +
                            (String)timer_->Get_data_time_().month_ + ".csv",
                        FILE_APPEND);
  } else
    dataFile_ = SD.open("/File.csv", FILE_APPEND);
#endif
#ifdef __AVR__
  if (timer_ != nullptr)
    dataFile_ = SD.open("/" + (String)timer_->Get_data_time_().date_ + "." +
                            (String)timer_->Get_data_time_().month_ + ".csv",
                        FILE_WRITE);
  else
    dataFile_ = SD.open("/File.csv", FILE_WRITE);
#endif
  if (dataFile_) {
    if (timer_ != nullptr) {
      dataFile_.print(timer_->Get_data_time_().date_);
      dataFile_.print(".");
      dataFile_.print(timer_->Get_data_time_().month_);
      dataFile_.print(".");
      dataFile_.print(timer_->Get_data_time_().year_);
      dataFile_.print(" ");
      dataFile_.print(timer_->Get_data_time_().hour_);
      dataFile_.print(":");
      dataFile_.print(timer_->Get_data_time_().minute_);
      dataFile_.print(":");
      dataFile_.print(0);
      dataFile_.print(";");
    }
    if (data_ != nullptr) {
      for (int i = 0; i < data_->GetDataFromSensors().getSize(); ++i) {
        switch (data_->GetDataFromSensors().get(i).getSensorDataType()) {
          case SensorDataType::Temperature:
            dataFile_.print("Temperature");
            break;
          case SensorDataType::Pressure:
            dataFile_.print("Pressure");
            break;
          case SensorDataType::Humidity:
            dataFile_.print("Humidity");
            break;
          case SensorDataType::Co2:
            dataFile_.print("Co2");
            break;
          default:
            dataFile_.print("Other");
            break;
        }
        dataFile_.print(";");
        PrintData(data_->GetDataFromSensors().get(i));
        dataFile_.print(";");
      }
    }
    dataFile_.print("\n");
    dataFile_.close();
  } else {
    Serial.println("error opening file");
  }
};
