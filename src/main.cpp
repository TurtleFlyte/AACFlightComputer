#include <Arduino.h>
#include <Wire.h>

#include <FlightTask.h>

TaskHandle_t g_flight_task;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {;}

  Wire.begin();
  Wire.setClock(400000);

  s_imu.init();
  s_baro.init();

  xTaskCreatePinnedToCore(
    flightTask,
    "FlightTask",
    8192,
    NULL,
    4,
    &g_flight_task,
    0);
}

void loop() { }