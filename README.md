# winsen-ze03-arduino-library

> Library to use Winston ZE03 sensor series.

## Installation

1) [Download The .zip file](https://github.com/fega/winsen-ze03-arduino-library/archive/master.zip)

2) Import it.
![Image importing an Arduino library](https://www.arduino.cc/en/uploads/Guide/ImportLibraryFromZIPFile.png)

## Usage

The library includes two modes: an active mode and a Question and answer mode.

### Question and Answer mode
To use the question an answer mode (for an Arduino MEGA):
```cpp
#include <WinsenZE03.h>

WinsenZE03 sensor;

void setup() {
    Serial3.begin(9600); // Initialize the Serial port
    sensor.begin(&Serial3, CO); // Init the sensor, don't forget the "&"

    sensor.setAs(QA); // use ACTIVE, for the active mode
    Serial.begin(9600);
}
void loop() {
    float ppm = sensor.readManual(); //Read the sensor
    Serial.println(ppm);
}
```
## API
### WinsenZE03.begin(&Serial, type)
Initialize the sensor to listen the Serial provided, the following types are supported:

CO,
SO2,
NO2,
O2,
NH3,
H2S,
HF,
CL2 and
O3
### WinsenZE03.setAs(ACTIVE || QA)
Sets the sensor to Active `.setAs(ACTIVE)`  or Question and Answer mode `.setAs(QA)`
### WinsenZE03.readManual()
Reads the sensor in QA mode and returns a Float with the result, if the read process suffers a problem, it returns -1

### WinsenZE03.readContinuous()
Reads the sensor in active mode and returns a Float with the result if Serial data is available, if the read process suffers a problem, it returns -1

## License

MIT © [Fabian Enrique Gutierrez](fabiangutierrez.co)
