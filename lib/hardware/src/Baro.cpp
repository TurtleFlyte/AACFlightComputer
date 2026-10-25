#include <Baro.h>

bool Baro::init(TwoWire& twire) {
    if (!baro.begin(BMP085_ULTRAHIGHRES, &twire)) return false;

    return true;
}

void Baro::update(Sample& sample) {
    float pres = static_cast<float>(baro.readPressure());
    float temp = baro.readTemperature();

    if (pres < 30000.0f || pres > 110000.0f) return;

    sample.pressure_pa = pres;
    sample.temp_c = temp;
}