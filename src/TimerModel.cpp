#include "TimerModel.h"

void TimerModel::SetDataAndTime(int16_t year, int8_t month, int8_t date, int8_t weekday,
                                int8_t hours, int8_t minutes, int8_t seconds) {
  data_time_.year_ = year;
  data_time_.month_ = month;
  data_time_.date_ = date;
  data_time_.weekday_ = weekday;
  data_time_.hour_ = hours;
  data_time_.minute_ = minutes;
  data_time_.second_ = seconds;
  SetUpTimeOnModule();
};

void TimerModel::SetDataAndTime(DateAndTime date_time) {
  data_time_ = date_time;
  SetUpTimeOnModule();
};

const TimerModel::DateAndTime& TimerModel::Get_data_time_() const { return data_time_; };
