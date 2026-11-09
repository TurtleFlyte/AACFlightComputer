#pragma once
#include <cstdint>

struct Sample {
    uint32_t time_ms;
    float ax, ay, az;
    float gx, gy, gz;
    float temp_c;
    float pressure_pa;
    float alt_m;
    int dropped;
};