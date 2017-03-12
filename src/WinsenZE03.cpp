/*
  WinsenZE03.cpp - This library allows you to set and read the ZE03 Winsen Sensor module.
  Created by Fabian Gutierrez, March 12, 20017.
  MIT.
*/

#include "Arduino.h"
#include "WinsenZE03.h"

WinsenZE03::WinsenZE03(HardwareSerial &s)
{
  s.begin(9600);
  _s = s;
}

void WinsenZE03::setAsContinuous(){
  // Send the command
  byte message[] = {0xFF,0x01, 0x78, 0x03, 0x00, 0x00, 0x00, 0x00, 0x83};
  _s.write(message,sizeof(message));
  
  // Wait for the response
  delay(1000);
  
  //Flush the incomming buffer
   while(_s.available()>0){
    byte c = c.read();
  }
}

void WinsenZE03::setAsManual(){
  // Send the command
  byte message[] = {0xFF,0x01, 0x78, 0x04, 0x00, 0x00, 0x00, 0x00, 0x83};
  _s.write(message,sizeof(message));
  
  // Wait for the response
  delay(1000);
  
  //Flush the incomming buffer
   while(_s.available()>0){
    byte c = c.read();
  }
}

float WinsenZE03::readContinuous(){
  if (_s.available() > 0) {
    byte measure[8];
    _s.readBytes(measure,9);
    // incomingByte = _s.read();
    float ppm = measure[2]*256+measure[3];
    return ppm
  }
}

float WinsenZE03::readManual(){
  // message to be sended
  byte message[] = {0xFF,0x01, 0x78, 0x03, 0x00, 0x00, 0x00, 0x00, 0x84};
  _s.write(message,sizeof(message));
  // space to the response
  byte measure[8]={0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  // result variable
  float ppm=0;
  // wait for the response
  delay(2000);
  // read and calculate
  if (_s.available() > 0) {
    _s.readBytes(measure,9);
    if (measure[0]==0xff && measure[1]==0x78){
      _s.readBytes(measure,9);
    }
    if (measure[0]==0xff && measure[1]==0x86){
      ppm = measure[2]*256+measure[3];
    }else{
      co=-1;
    }
  }
  return ppm
}