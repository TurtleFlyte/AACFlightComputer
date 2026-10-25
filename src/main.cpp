#include <Arduino.h>
#include <Adafruit_BMP085.h>
#include <CoreTypes.h>
#include <ImuLowG.h>

#include <Adafruit_Sensor.h>
#include <Wire.h>

static Adafruit_BMP085 bmp;
static ImuLowG imu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {;}

  Wire.begin();
  Wire.setClock(400000);

  imu.init();

  if (!bmp.begin(BMP085_I2CADDR)) {
    Serial.println("Failed to find BMP085 chip");
    while (1) {
      delay(10);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Sample sample;
  imu.update(sample);

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

  Serial.print("Temperature: ");
  Serial.print(sample.temp);
  Serial.println(" degC");

  Serial.println("");

  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");

  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");

  Serial.print("Real altitude = ");
  Serial.print(bmp.readAltitude(101500));
  Serial.println(" meters");

  Serial.println();
  delay(100);
}