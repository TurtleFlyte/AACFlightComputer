#include <ImuLowG.h>

bool ImuLowG::init(TwoWire& twire) {
    if (!mpu.begin(MPU6050_I2CADDR_DEFAULT, &twire)) return false;

    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);

    return true;
}

void ImuLowG::update(Sample& sample) {
    sensors_event_t a, g, t;

    if (!mpu.getEvent(&a, &g, &t)) {
        return;
    }

    sample.ax = a.acceleration.x;
    sample.ay = a.acceleration.y;
    sample.az = a.acceleration.z;
    sample.gx = g.gyro.x;
    sample.gy = g.gyro.y;
    sample.gz = g.gyro.z;
    sample.temp = t.temperature;
}