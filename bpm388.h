#include "esphome.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BMP3XX.h"

class BMP3XXSensor : public PollingComponent {
 public:
  Adafruit_BMP3XX bmp;
  Sensor *temperature_sensor = new Sensor();
  Sensor *pressure_sensor = new Sensor();

  BMP3XXSensor() : PollingComponent(15000) { }

  void setup() override {
    bmp.begin_I2C();
  }

  void update() override {
    // This is the actual sensor reading logic.
    float temperature = bmp.readTemperature();
    temperature_sensor->publish_state(temperature);

    int pressure = bmp.readPressure();
    pressure_sensor->publish_state(pressure / 100.0);
  }
};