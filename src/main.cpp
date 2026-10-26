#include <Arduino.h>
#include <CoreTypes.h>
#include <ImuLowG.h>
#include <Baro.h>

#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "config.h"

static Baro s_baro;
static ImuLowG s_imu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {;}

  Wire.begin();
  Wire.setClock(400000);

  s_imu.init();
  s_baro.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Sample sample{};
  s_imu.update(sample);
  s_baro.update(sample);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(sample.ax);
  Serial.print(", Y: ");
  Serial.print(sample.ay);
  Serial.print(", Z: ");
  Serial.print(sample.az);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(sample.gx);
  Serial.print(", Y: ");
  Serial.print(sample.gy);
  Serial.print(", Z: ");
  Serial.print(sample.gz);
  Serial.println(" rad/s");

  Serial.println("");

  Serial.print("Temperature: ");
  Serial.print(sample.temp_c);
  Serial.println(" *C");

  Serial.print("Pressure: ");
  Serial.print(sample.pressure_pa);
  Serial.println(" Pa");

  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  const float alt = 44330 * (1.0 - pow(sample.pressure_pa / 101500, 0.1903));
  Serial.print("Real Altitude: ");
  Serial.print(alt);
  Serial.println(" meters");

  Serial.println();
  delay(LOOP_PERIOD_MS);
}