#pragma once
#include <Arduino.h>

#include "Module.h"

class TimerModel : public Module {
 public:
  struct DateAndTime {
    uint16_t year_ = 2023;
    uint8_t month_ = 2;
    uint8_t date_ = 13;
    uint8_t weekday_ = 1;
    uint8_t hour_ = 14;
    uint8_t minute_ = 0;
    uint8_t second_ = 0;
  };

  virtual void SetDataAndTime(int16_t year, int8_t month, int8_t date, int8_t weekday, int8_t hours,
                              int8_t minutes, int8_t seconds);
  virtual void SetDataAndTime(DateAndTime date_time);
  const DateAndTime& Get_data_time_() const;

 protected:
  virtual void SetUpTimeOnModule() = 0;  // Function for setting the selected
                                         // date and time in the module
  DateAndTime data_time_;
};
