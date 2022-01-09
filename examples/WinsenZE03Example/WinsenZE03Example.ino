/*
  WinsenZE03.h - This library allows you to set and read the ZE03 Winsen Sensor module.
	More information: https://github.com/fega/winsen-ze03-arduino-library
  Created by Fabian Gutierrez <fega.hg@gmail.com>, March 17, 2017.
  MIT.
*/

#include <WinsenZE03.h>

WinsenZE03 sensor;


void setup() {
  Serial2.begin(9600);
  Serial.begin(9600);
  sensor.begin(&Serial2, CO);
  if (sensor.setAs(QA))
  {
    Serial.println("Set Mode Sucess");
  }
  else
  {
    Serial.println("Set Mode Fail");
  }
}
void loop() {
  float ppm = sensor.readManual();  // will return -1 if CRC fails and -2 if timeout
  Serial.print("CO: ");
  Serial.print(ppm);
  Serial.println(" PPM");
}