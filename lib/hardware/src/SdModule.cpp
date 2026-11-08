#include <SdModule.h>
#include <SdFat.h>

static constexpr uint64_t LOG_SIZE = 40 * 1000/50 * 1200;
static constexpr char LOG_HEADER[] = "time_ms,ax,ay,az,gx,gy,gz,temp_c,pressure_pa,alt_m,dropped\n";

bool SdModule::init(const uint8_t cs_pin) {
    if (!m_sd.begin(cs_pin, SD_SCK_MHZ(50))) return false;

    // Find next file to write to, /log_NNN.csv
    char file_name[24];
    for (int i = 0; i < 1000; ++i) {
        snprintf(file_name, sizeof(file_name), "/log_%03d.csv", i);
        if (!m_sd.exists(file_name)) break;
    }

    if (!m_log_file.open(file_name, O_WRONLY | O_CREAT | O_EXCL)) return false;

    // m_log_file.preAllocate(LOG_SIZE);
    m_log_file.write(LOG_HEADER, sizeof(LOG_HEADER) - 1);

    m_ready = true;
    return true;
}

bool SdModule::write(const Sample &sample) {
    if (!m_ready) return false;

    int line_size = snprintf(m_log_line, sizeof(m_log_line),
        "%lu,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%d\n",
        static_cast<unsigned long>(sample.time_ms),
        sample.ax, sample.ay, sample.az,
        sample.gx, sample.gy, sample.gz,
        sample.temp_c, sample.pressure_pa, sample.alt_m,
        sample.dropped);

    if (line_size <= 0 || line_size >= static_cast<int>(sizeof(m_log_line))) return false;

    if (m_log_file.write(m_log_line, line_size) != static_cast<size_t>(line_size)) return false;

    return true;
}

void SdModule::sync() {
    if (m_ready && !m_log_file.sync()) return;
}
