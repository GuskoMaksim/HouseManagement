#pragma once
#include <LiquidCrystal_I2C.h>

#include "ManagerSensor.h"
#include "Module.h"
#include "TimerModel.h"

class DisplayLCD2004 : public Module {
   private:
    LiquidCrystal_I2C lcd_;
    TimerModel *timer_ = nullptr;
    ManagerSensor *data_ = nullptr;
    uint8_t lsdTimeOff = 0;
    uint8_t lsdTimeOn = 8;
    bool lsdBacklightOn = true;
    const uint32_t refresh_interval_display_ms = 1000;
    uint32_t timer_to_update_display_ms = refresh_interval_display_ms + 1;
    void printTime(uint8_t var) {
        if (var < 10) lcd_.print("0");
        lcd_.print(var);
    }
    void PrintData(Variant var);

   public:
    void Update();
    bool Init();
    void AddTimer(TimerModel *timer) { timer_ = timer; }
    void AddManagerSensor(ManagerSensor *data) { data_ = data; }
    DisplayLCD2004();
    ~DisplayLCD2004();
};
