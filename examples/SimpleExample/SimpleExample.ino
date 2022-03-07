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
