#include <ImuLowG.h>

bool ImuLowG::init(TwoWire& twire) {
    if (!m_mpu.begin(MPU6050_I2CADDR_DEFAULT, &twire)) return false;

    m_mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    m_mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
    m_mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);

    return true;
}

void ImuLowG::update(Sample& sample) {
    sensors_event_t a, g, t;

    if (!m_mpu.getEvent(&a, &g, &t)) {
        return;
    }

    sample.ax = a.acceleration.x;
    sample.ay = a.acceleration.y;
    sample.az = a.acceleration.z;
    sample.gx = g.gyro.x;
    sample.gy = g.gyro.y;
    sample.gz = g.gyro.z;
}