#include <CoreTypes.h>
#include <config.h>
#include "FlightTask.h"

Baro s_baro;
ImuLowG s_imu;

void FlightTask(void* arg) {
    s_imu.init();
    s_baro.init();

    auto logger_queue = static_cast<QueueHandle_t>(arg);

    for (;;) {
        Sample sample{};
        sample.time_ms = millis();

        s_imu.update(sample);
        s_baro.update(sample);

        if (!xQueueSend(logger_queue, &sample, 0)) sample.dropped++;

        /* Print out the values */
        // Serial.print("Acceleration X: ");
        // Serial.print(sample.ax);
        // Serial.print(", Y: ");
        // Serial.print(sample.ay);
        // Serial.print(", Z: ");
        // Serial.print(sample.az);
        // Serial.println(" m/s^2");
        //
        // Serial.print("Rotation X: ");
        // Serial.print(sample.gx);
        // Serial.print(", Y: ");
        // Serial.print(sample.gy);
        // Serial.print(", Z: ");
        // Serial.print(sample.gz);
        // Serial.println(" rad/s");
        //
        // Serial.println("");
        //
        // Serial.print("Temperature: ");
        // Serial.print(sample.temp_c);
        // Serial.println(" *C");
        //
        // Serial.print("Pressure: ");
        // Serial.print(sample.pressure_pa);
        // Serial.println(" Pa");
        //
        // // Calculate altitude assuming 'standard' barometric
        // // pressure of 1013.25 millibar = 101325 Pascal
        // const float alt = 44330 * (1.0 - pow(sample.pressure_pa / 101500, 0.1903));
        // Serial.print("Real Altitude: ");
        // Serial.print(alt);
        // Serial.println(" meters");
        //
        // Serial.println();
        vTaskDelay(LOOP_PERIOD_MS / portTICK_PERIOD_MS);
    }
}