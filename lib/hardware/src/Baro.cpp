#include <Baro.h>

bool Baro::init(TwoWire& twire) {
    if (!m_bmp.begin(BMP085_ULTRAHIGHRES, &twire)) return false;

    return true;
}

void Baro::update(Sample& sample) {
    float pres = static_cast<float>(m_bmp.readPressure());
    float temp = m_bmp.readTemperature();

    if (pres < 30000.0f || pres > 110000.0f) return;

    sample.pressure_pa = pres;
    sample.temp_c = temp;
}