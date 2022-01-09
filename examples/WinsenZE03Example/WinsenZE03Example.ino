/*
  WinsenZE03.h - This library allows you to set and read the ZE03 Winsen Sensor module.
	More information: https://github.com/fega/winsen-ze03-arduino-library
  Created by Fabian Gutierrez <fega.hg@gmail.com>, March 17, 2017.
  MIT.
*/

#include <WinsenZE03.h>

WinsenZE03 sensor;


void setup() {
  Serial3.begin(9600);
  Serial.begin(9600);
  sensor.begin(&Serial3, CO);
	sensor.setAs(QA);
}
void loop() {
 float ppm = sensor.readManual();
 Serial.println(ppm);
}
