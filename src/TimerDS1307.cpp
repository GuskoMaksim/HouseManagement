#include "TimerDS1307.h"

TimerDS1307::TimerDS1307() : Rtc(Wire) {};

bool TimerDS1307::wasError() {
  uint8_t error = Rtc.LastError();
  if (error != 0) {
    switch (error) {
      case Rtc_Wire_Error_None:
        Serial.println("(none?!)");
        break;
      case Rtc_Wire_Error_TxBufferOverflow:
        Serial.println("transmit buffer overflow");
        break;
      case Rtc_Wire_Error_NoAddressableDevice:
        Serial.println("no device responded");
        break;
      case Rtc_Wire_Error_UnsupportedRequest:
        Serial.println("device doesn't support request");
        break;
      case Rtc_Wire_Error_Unspecific:
        Serial.println("unspecified error");
        break;
      case Rtc_Wire_Error_CommunicationTimeout:
        Serial.println("communications timed out");
        break;
    }
    return true;
  }
  return false;
};

bool TimerDS1307::Init() {
  Rtc.Begin();
  if (wasError()) return false;
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  if (!Rtc.IsDateTimeValid()) {
    // Common Causes:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing
    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }
  if (!Rtc.GetIsRunning()) {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }
  now = Rtc.GetDateTime();
  if (now < compiled) {
    Serial.println("RTC is older than compile time, updating DateTime");
    Rtc.SetDateTime(compiled);
  } else if (now > compiled) {
    Serial.println("RTC is newer than compile time, this is expected");
  } else if (now == compiled) {
    Serial.println(
        "RTC is the same as compile time, while not expected all is still "
        "fine");
  }
  Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low);
  Update();
  return true;
};

void TimerDS1307::Update() {
  now = Rtc.GetDateTime();
  data_time_.year_ = now.Year();
  data_time_.month_ = now.Month();
  data_time_.date_ = now.Day();
  data_time_.weekday_ = now.DayOfWeek();
  data_time_.hour_ = now.Hour();
  data_time_.minute_ = now.Minute();
  data_time_.second_ = now.Second();
};

void TimerDS1307::SetUpTimeOnModule() {
  RtcDateTime newRtcTime(data_time_.year_, data_time_.month_, data_time_.weekday_, data_time_.hour_,
                         data_time_.minute_, data_time_.second_);
  Rtc.SetDateTime(newRtcTime);
};
