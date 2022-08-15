
#include "AsyncBMP180Wrapper.h"


void AsyncBMP180Wrapper::init() {
  if (!_pressureSensor.begin()) {
    log("Failed to start BMP180");
  } else {
    _step = 0;
    _initialized = true;
  }
}

void AsyncBMP180Wrapper::process() {
  if (!_initialized)
    return;
  if (_step == 0) {
    _step = 1;
    uint8_t wait = _pressureSensor.startTemperature();
    if (wait == 0) {
      log("Step 1 Wait ERR");
      _step = 0;
    } else {
      _delayTimer.start(wait);
    }
  }
  if (_delayTimer.available()) {
    _delayTimer.stop();
    if (_step == 1) {
      _step = 2;
      bool status = _pressureSensor.getTemperature(_lastT);
      if (status) {
        uint8_t wait = _pressureSensor.startPressure(3);
        if (wait == 0) {
          log("Step 1 Wait ERR");
          _step = 0;
        } else {
          _delayTimer.start(wait);
        }
      } else {
        log("Step 1 ERR");
        _step = 0;
      }
    } else if (_step == 2) {
      _step = 3;
      bool status = _pressureSensor.getPressure(_lastP, _lastT);
      if (status) {
        _lastP0 = _pressureSensor.sealevel(_lastP, _altitude);
        _delayTimer.start(5000);
      } else {
        log("Step 2 ERR");
        _step = 0;
      }
    } else if (_step == 3) {
      _step = 0;
	  _ready = true;
    }
  }
}

bool AsyncBMP180Wrapper::ready() {
  return _ready;
}

float AsyncBMP180Wrapper::getT() {
  return (float)_lastT;
}

float AsyncBMP180Wrapper::getP() {
  return (float)_lastP;
}

float AsyncBMP180Wrapper::getP0() {
  return (float)_lastP0;
}

int32_t AsyncBMP180Wrapper::convertToRaw(double val) {
  float fval = (float)val;
  int16_t raw = (int16_t)fval;
  double decimal = fval - raw;
  decimal = decimal * 100;
  uint16_t dec = (uint16_t)decimal;
  int32_t res = (int32_t)raw << 16 || dec;
  return res;
}

int32_t AsyncBMP180Wrapper::getRawT() {
  return convertToRaw(_lastT);
}

int32_t AsyncBMP180Wrapper::getRawP() {
  return convertToRaw(_lastP);
}

int32_t AsyncBMP180Wrapper::getRawP0() {
  return convertToRaw(_lastP0);
}

void AsyncBMP180Wrapper::log(char *msg) {
  if (logger)
    logger(msg);
}

void AsyncBMP180Wrapper::log(String msg) {
  if (logger)
    logger(msg.c_str());
}
