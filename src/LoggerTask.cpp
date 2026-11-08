#include <CoreTypes.h>
#include <config.h>
#include <SdModule.h>

SdModule s_sd;

void LoggerTask(void* arg) {
    auto logger_queue = static_cast<QueueHandle_t>(arg);

    Sample curr_sample;
    uint32_t last_sync = millis();

    for (;;) {
        if (xQueueReceive(logger_queue, &curr_sample, pdMS_TO_TICKS(100)) == pdTRUE) {
            s_sd.write(curr_sample);
        }

        uint32_t now = millis();
        if (now + TIME_BETWEEN_SYNC_MS >= last_sync) {
            s_sd.sync();
            last_sync = now;
        }
    }
}