#include "DisplayLCD2004.h"

DisplayLCD2004::DisplayLCD2004() : lcd_(0x27, 20, 4) {
  Init();
  lcd_.backlight();
}

void DisplayLCD2004::PrintData(Variant var) {
  switch (var.getValueType()) {
    case ValueType::Bool:
      lcd_.print(var.getValue<bool>());
      break;
    case ValueType::Float:
      lcd_.print(var.getValue<float>());
      break;
    case ValueType::Int32_t:
      lcd_.print(var.getValue<int32_t>());
      break;
  }
};

void DisplayLCD2004::Update() {
  if (millis() - timer_to_update_display_ms > refresh_interval_display_ms) {
    timer_to_update_display_ms = millis();
    if (timer_ != nullptr) {
      lcd_.setCursor(0, 0);
      printTime(timer_->Get_data_time_().date_);
      lcd_.print(".");
      printTime(timer_->Get_data_time_().month_);
      lcd_.print("  ");
      printTime(timer_->Get_data_time_().hour_);
      lcd_.print(":");
      printTime(timer_->Get_data_time_().minute_);
      lcd_.print(":");
      printTime(timer_->Get_data_time_().second_);
      if (timer_->Get_data_time_().hour_ >= lsdTimeOff &&
          timer_->Get_data_time_().hour_ <= lsdTimeOn) {
        if (lsdBacklightOn) {
          lsdBacklightOn = false;
          lcd_.noBacklight();
        }
      } else if (!lsdBacklightOn) {
        lsdBacklightOn = true;
        lcd_.backlight();
      }
    }
    if (data_ != nullptr) {
      lcd_.setCursor(0, 1);
      for (int i = 0; i < data_->GetDataFromSensors().getSize(); i++) {
        switch (data_->GetDataFromSensors().get(i).getSensorDataType()) {
          case SensorDataType::Temperature:
            lcd_.print("T:");
            break;
          case SensorDataType::Pressure:
            lcd_.print("P:");
            break;
          case SensorDataType::Humidity:
            lcd_.print("H:");
            break;
          case SensorDataType::Co2:
            lcd_.print("C:");
            break;
          default:
            lcd_.print("O:");
            break;
        }
        PrintData(data_->GetDataFromSensors().get(i));
        lcd_.print(" ");
      }
    }
  }
}

bool DisplayLCD2004::Init() {
  lcd_.init();
  return true;
}

DisplayLCD2004::~DisplayLCD2004() {}
