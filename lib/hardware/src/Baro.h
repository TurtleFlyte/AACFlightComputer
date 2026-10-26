#pragma once
#include <Adafruit_BMP085.h>
#include <CoreTypes.h>

class Baro {
public:
    bool init(TwoWire& twire = Wire);
    void update(Sample& sample);

private:
    Adafruit_BMP085 m_baro;
};