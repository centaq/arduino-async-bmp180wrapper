# arduino-async-bmp180wrapper
BMP180 Async Wrapper for contiinous temperature/pressure reading in the background

Library which allows to put some of the data retrieving process in the background.

## Requirements
For this library to work you need to also install:
- Sparkfun BMP180 - https://github.com/sparkfun/BMP180_Breakout
- Timers - https://github.com/centaq/arduino-simple-timers

## Example
### Simple pressure retrieve example
	#include "AsyncBMP180Wrapper.h"


	AsyncBMP180Wrapper bmp180;

	void setup() {
	  bmp180.init(); 
	}
	bool giveMeData = true;

	void loop() {
	  bmp180.process();
	  if (giveMeData && bmp180.ready()) {
		float pressure = bmp180.getP();
		int32_t pressureRaw = bmp180.getRawP();
		giveMeData = false;
	  }
	}
	
The basic thing you have to remember is to put `process` function in your program loop function.
Then (when data is ready) you can access data any time it is needed.

### Full example
	#include "AsyncBMP180Wrapper.h"

	#define ALTITUDE 130.0

	AsyncBMP180Wrapper bmp180(ALTITUDE);

	void logger(char *msg) {
	  Serial.println(msg);
	}

	void setup() {
	  bmp180.init(); 
	  bmp180.logger = *logger;
	  
	}
	bool giveMeData = true;

	void loop() {
	  bmp180.process();
	  if (giveMeData && bmp180.ready()) {
		float pressure = bmp180.getP();
		int32_t pressureRaw = bmp180.getRawP();
		
		float pressureSeaLevel = bmp180.getP0();
		int32_t pressureSeaLevelRaw = bmp180.getRawP0();
		
		float temperature = bmp180.getT();
		int32_t temperatureRaw = bmp180.getRawT();
		
		giveMeData = false;
	  }
	}

As you can see, you can specify an ALTITUDE value in the constructor of the wrapper to provide correct value of sea level pressure.
