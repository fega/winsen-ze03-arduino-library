/*
  Morse.h - This library allows you to set and read the ZE03 Winsen Sensor module.
  Created by Fabian Gutierrez, March 12, 20017.
  MIT.
*/

#ifndef WinsenZE03_h
#define WinsenZE03_h

#include "Arduino.h"
#define CO 1
#define SO2 2
#define NO2 2
#define O2 2
#define NH3 1
#define H2S 1
#define HF 1
#define CL2 2
#define O3 2

#define timeout 1500  // default timeout of 1.5sec

#define QA false
#define ACTIVE true

class WinsenZE03
{
  public:
    WinsenZE03();
    void begin(Stream *ser, int type);
    bool setAs(bool active);
    float readManual(); 		// will return -1 if CRC fails and -2 if timeout
    float readContinuous();		// will return -1 if CRC fails or timeout
  private:
    void debugPrint(byte arr[]);
    bool CRC(unsigned char *i, unsigned char ln); // to check the incoming data is valid or not.
    Stream *_s; //Serial1 - Serial3 are USARTClass objects.
    int _type;
};

#endif
