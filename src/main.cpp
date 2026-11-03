#include <Arduino.h>
#include <Wire.h>

#include <FlightTask.h>

TaskHandle_t g_flight_task;

void setup() {
    Serial.begin(115200);
    while (!Serial) {;}

    Wire.begin();
    Wire.setClock(400000);

    xTaskCreatePinnedToCore(
        FlightTask,
        "FlightTask",
        8192,
        nullptr,
        3,
        &g_flight_task,
        0);
}

void loop() { vTaskDelete(nullptr); }