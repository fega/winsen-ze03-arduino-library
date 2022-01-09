/*
  WinsenZE03.h - This library allows you to set and read the ZE03 Winsen Sensor module.
  Created by Fabian Gutierrez, March 12, 20017.
  MIT.
*/

#include "Arduino.h"
#include "WinsenZE03.h"
#define DEVMODE true //Set as true to debug

WinsenZE03::WinsenZE03() {
  _s  = NULL;
}

void WinsenZE03::begin(Stream *ser, int type) {
  _s = ser;
  _type = type;
}

bool WinsenZE03::setAs(bool active) {
  byte setConfig[] = {0xFF, 0x01, 0x78, 0x04, 0x00, 0x00, 0x00, 0x00, 0x83};//QA config
  byte response[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  boolean sucess = false;
  if (active) {
    setConfig[3] = 0x03;
    setConfig[8] = 0x84;

    /*
      Roughly it takes 1.04 ms of time between 2 byte transfer @9600 baudrate.
      Therefore to receive 9 bytes at 9600 baud it would take around 1.04*9  = 9.36ms
      So if serial available shows >0 byte available then _s->readBytes(measure,9); function should not take more then 10ms theoritically.
      So to be on safe side seting the serial timeout to 50ms in active mode.
    */
    _s->setTimeout(50);
  }
  _s->flush(); // flush all tx data from buffer

  _s->write(setConfig, sizeof(setConfig));
  // Wait for the response
  delay(1000);
  //Flush the incomming buffer
  if (_s->available() > 0) {
    _s->readBytes(response, 9);
    if (CRC(response, 9))
    {
      //CRC is valid now checking byte 2 is 1 or 0
      if (response[2] == 0x01)
      {
        // Mode set sucess
        sucess = true;
      }
    }
  }
  while (_s->available() > 0) {
    byte c = _s->read();
  }
  return sucess;
}

float WinsenZE03::readContinuous() {
  if (_s->available() > 0) {
    float ppm;
    byte measure[9];  // in total 9 bytes will be received
    _s->readBytes(measure, 9);
    if (CRC(measure, 9)) // added a proper CRC check inted of just two byte checking
    {
      ppm = measure[2] * 256 + measure[3]; // this formula depends of the sensor is in the dataSheet
      if (_type == 2)
      {
        ppm = ppm * 0.1;
      }
    }
    else {
      ppm = -1;
    }
    return ppm;
  }
}

float WinsenZE03::readManual() {
  float ppm;
  byte petition[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; // Petition to get a single result
  byte measure[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Space for the response

  _s->flush();  // making sure that there is no past data left out in internal Serial buffere to be transmit.

  // Before requesting new data clearing out the past Serial data in received buffer if any.
  while (_s->available() > 0)
  {
    char dummy_ch = _s->read();
  }

  _s->write(petition, sizeof(petition)); // Sending out request packets
  _s->flush(); // making sure that complete request has been made

  unsigned long oldmillis = millis();
  boolean timeout_error = false;

  //delay(1500);

  //insted of delay added an timeout as it may happen data is received before delay time.
  while (_s->available() < 9)
  {
    delay(10);
    if (millis() - oldmillis >= timeout)
    {
      timeout_error = true;
      break;
    }
  }

  // read
  //if (_s->available() > 0)

  if (!timeout_error)
  {
    _s->readBytes(measure, 9);
    // calculate
    //if (measure[0]==0xff && measure[1]==0x86){
    if (CRC(measure, 9)) // added a proper CRC check inted of just two byte checking
    {
      ppm = measure[2] * 256 + measure[3]; // this formula depends of the sensor is in the dataSheet
      if (_type == 2)
      {
        ppm = ppm * 0.1;
      }
    }
    else {
      ppm = -1;
    }
  }
  else
  {
    ppm = -2; // return -2 if timout.
  }
  return ppm;
}

void WinsenZE03::debugPrint(byte arr[]) {
  Serial.print(arr[0], HEX); Serial.print(" ");
  Serial.print(arr[1], HEX); Serial.print(" ");
  Serial.print(arr[2], HEX); Serial.print(" ");
  Serial.print(arr[3], HEX); Serial.print(" ");
  Serial.print(arr[4], HEX); Serial.print(" ");
  Serial.print(arr[5], HEX); Serial.print(" ");
  Serial.print(arr[6], HEX); Serial.print(" ");
  Serial.print(arr[7], HEX); Serial.print(" ");
  Serial.println(arr[8], HEX);
}

bool WinsenZE03::CRC(unsigned char *i, unsigned char ln)
{
  unsigned char j, tempq = 0;
  i += 1; // for calculating checksum we need to ignore the byte0
  for (j = 0; j < (ln - 2); j++)
  {
    tempq += *i;
    i++;
  }
  tempq = (~tempq) + 1;
  if (tempq == *i)
  {
    return true;  // return true if the calculated CRC matched the received CRC
  }
  else
  {
    return false; // return false on CRC fail it means received data is not valid
  }
}
