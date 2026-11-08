#pragma once
#include "CoreTypes.h"
#include <SdFat.h>

class SdModule {
public:
    bool init(uint8_t cs_pin);
    bool write(const Sample& sample);

    void sync();
private:
    SdFat m_sd;
    File m_log_file;

    char m_log_line[200] = {};

    int m_errors = 0;
    bool m_ready = false;
};