/*
  WinsenZE03.h - This library allows you to set and read the ZE03 Winsen Sensor module.
	More information: https://github.com/fega/winsen-ze03-arduino-library
  Created by Fabian Gutierrez <fega.hg@gmail.com>, Apr 3, 2017.
  MIT.
*/

#include <WinsenZE03.h>

WinsenZE03 sensor1;
WinsenZE03 sensor2;
WinsenZE03 sensor3;


void setup() {
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial.begin(9600);

  sensor1.begin(&Serial1, SO2);
  sensor2.begin(&Serial2, NO2);
  sensor3.begin(&Serial3, CO);

  sensor1.setAs(QA);
  sensor2.setAs(QA);
  sensor3.setAs(QA);
}
void loop() {
 float ppm = sensor1.readManual();
 Serial.println(ppm);
 ppm = sensor2.readManual();
 Serial.println(ppm);
 ppm = sensor3.readManual();
 Serial.println(ppm);
 Serial.println("---");
}
