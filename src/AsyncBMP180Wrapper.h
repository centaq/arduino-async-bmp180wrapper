#ifndef _AsyncBMP180Wrapper_h
#define _AsyncBMP180Wrapper_h

#include <SFE_BMP180.h>

#include "Arduino.h"
#include "Timers.h"


class AsyncBMP180Wrapper {
  private:
    SFE_BMP180 _pressureSensor;
    Timers _delayTimer;
    Timers _waitingTimer;
    float _altitude;
    bool _waiting;
    uint8_t _step;
    bool _initialized;
    double _lastT, _lastP, _lastP0;
    int32_t convertToRaw(double val);
    void log(char *msg);
    void log(String msg);
  public:
    AsyncBMP180Wrapper() : AsyncBMP180Wrapper(0) {}
    AsyncBMP180Wrapper(float altitude) { _altitude = altitude; }
    void init();
    void process();
    float getT();
    float getP();
    float getP0();
    int32_t getRawT();
    int32_t getRawP();
    int32_t getRawP0();
    void (*logger)(char *msg);
};

#endif