#include "TimerDS1302.h"

TimerDS1302::TimerDS1302(uint8_t DAT, uint8_t CLK, uint8_t RST)
    : myWire(DAT, CLK, RST), Rtc(myWire) {};

bool TimerDS1302::Init() {
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Serial.println();
  if (!Rtc.IsDateTimeValid()) {
    // Common Causes:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing
    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }

  if (Rtc.GetIsWriteProtected()) {
    Serial.println("RTC was write protected, enabling writing now");
    Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning()) {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }
  now = Rtc.GetDateTime();
  if (now < compiled) {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  } else if (now > compiled) {
    Serial.println("RTC is newer than compile time. (this is expected)");
  } else if (now == compiled) {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }
  Update();
  return true;
};

void TimerDS1302::Update() {
  now = Rtc.GetDateTime();
  data_time_.year_ = now.Year();
  data_time_.month_ = now.Month();
  data_time_.date_ = now.Day();
  data_time_.weekday_ = now.DayOfWeek();
  data_time_.hour_ = now.Hour();
  data_time_.minute_ = now.Minute();
  data_time_.second_ = now.Second();
};

void TimerDS1302::SetUpTimeOnModule() {
  RtcDateTime newRtcTime(data_time_.year_, data_time_.month_, data_time_.weekday_, data_time_.hour_,
                         data_time_.minute_, data_time_.second_);
  Rtc.SetDateTime(newRtcTime);
};
