/*
  WinsenZE03.h - This library allows you to set and read the ZE03 Winsen Sensor module.
  Created by Fabian Gutierrez, March 12, 20017.
  MIT.
*/

#include "Arduino.h"
#include "WinsenZE03.h"
#define DEVMODE true //Set as true to debug

WinsenZE03::WinsenZE03(){
  _s  = NULL;
}

void WinsenZE03::begin(Stream *ser, int type){
  _s = ser;
  _type=type;
}

void WinsenZE03::setAs(bool active){
  byte setConfig[] = {0xFF, 0x01, 0x78, 0x04, 0x00, 0x00, 0x00, 0x00, 0x83};//QA config
  byte response[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  if (active){
    setConfig[3] =0x03;
    setConfig[8] =0x84;
  }
  _s->write(setConfig,sizeof(setConfig));
  // Wait for the response
  delay(2000);
  //Flush the incomming buffer
  if (_s->available() > 0) {
    _s->readBytes(response,9);
  }
  while(_s->available()>0){
    byte c = _s->read();
  }
}

float WinsenZE03::readContinuous(){
  if (_s->available() > 0) {
    byte measure[8];
    _s->readBytes(measure,9);
    // incomingByte = _s.read();
    float ppm = measure[2]*256+measure[3];
    return ppm;
  }
}

float WinsenZE03::readManual(){
  float ppm;
  byte petition[] = {0xFF,0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};// Petition to get a single result
  byte measure[8]={0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};// Space for the response
  _s->write(petition,sizeof(petition));
  delay(1500);
  // read
  if (_s->available() > 0) {
    _s->readBytes(measure,9);
  }
  // calculate
  if (measure[0]==0xff && measure[1]==0x86){
    ppm = measure[2]*256+measure[3];// this formula depends of the sensor is in the dataSheet
    if (_type == 2){
      ppm = ppm*0.1;
    }
  }else{
    ppm=-1;
  }
  return ppm;
}

void WinsenZE03::debugPrint(byte arr[]){
  Serial.print(arr[0],HEX);Serial.print(" ");
  Serial.print(arr[1],HEX);Serial.print(" ");
  Serial.print(arr[2],HEX);Serial.print(" ");
  Serial.print(arr[3],HEX);Serial.print(" ");
  Serial.print(arr[4],HEX);Serial.print(" ");
  Serial.print(arr[5],HEX);Serial.print(" ");
  Serial.print(arr[6],HEX);Serial.print(" ");
  Serial.print(arr[7],HEX);Serial.print(" ");
  Serial.println(arr[8],HEX);
}
