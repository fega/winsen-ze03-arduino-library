/*
  WinsenZE03.h - This library allows you to set and read the ZE03 Winsen Sensor module.
  Created by Fabian Gutierrez, March 12, 20017.
  MIT.
*/

#ifndef WinsenZE03_h
#define WinsenZE03_h

#include "Arduino.h"


class WinsenZE03
{
  public:
    WinsenZE03(HardwareSerial s);
    void begin();
    void setAsContinuous();
    void setAsManual();
    float readManual();
    float readContinuous();
  private:
    HardwareSerial &_s;
    int _type;
};

#endif