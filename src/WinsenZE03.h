/*
  Morse.h - This library allows you to set and read the ZE03 Winsen Sensor module.
  Created by Fabian Gutierrez, March 12, 20017.
  MIT.
*/

#ifndef WinsenZE03_h
#define WinsenZE03_h

#include "Arduino.h"


class WinsenZE03
{
  public:
    WinsenZE03(USARTClass *ser, int type);
    WinsenZE03(UARTClass *ser, int type);
    void begin();
    void setAsContinuous();
    void setAsManual();
    float readManual();
    float readContinuous();
  private:
    void init();
    USARTClass *_serial; //Serial1 - Serial3 are USARTClass objects.
    UARTClass *_serial0;
    int _type;
};

#endif