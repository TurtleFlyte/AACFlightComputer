#pragma once
#include <Adafruit_MPU6050.h>
#include <CoreTypes.h>

class ImuLowG {
public:
    bool init(TwoWire& twire = Wire);
    void update(Sample& sample);

private:
    Adafruit_MPU6050 mpu;
};