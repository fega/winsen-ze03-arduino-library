#include <WinsenZE03.h>

WinsenZE03 sensor;


void setup() {
	sensor.begin(&Serial3, CO);
  Serial3.begin(9600);
	sensor.setAs(QA);
  Serial.begin(9600);

}
void loop() {
 float ppm = sensor.readManual();
 Serial.println(ppm);
}
