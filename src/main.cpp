#include <Arduino.h>
#include <Wire.h>

#include <FlightTask.h>
#include <LoggerTask.h>

#include "config.h"
#include "CoreTypes.h"

TaskHandle_t g_flight_task;
TaskHandle_t g_logger_task;

void setup() {
    Serial.begin(115200);
    while (!Serial) {;}

    Wire.setClock(400000);
    Wire.setPins(22, 23);
    Wire.begin();

    QueueHandle_t logger_queue = xQueueCreate(LOGGER_MAX_QUEUE_DEPTH, sizeof(Sample));

    s_sd.init(CS_PIN);

    xTaskCreate(
        FlightTask,
        "FlightTask",
        4096,
        logger_queue,
        3,
        &g_flight_task);

    xTaskCreate(
        LoggerTask,
        "LoggerTask",
        8192,
        logger_queue,
        1,
        &g_logger_task);
}

void loop() { vTaskDelete(nullptr); }