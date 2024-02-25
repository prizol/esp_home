#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
//#include "esphome/components/text_sensor/text_sensor.h"
//#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace fogymero_dal {

class FogymeroDalComponent : public PollingComponent, public uart::UARTDevice {
  public:

    void setup() override;
    void loop() override;
    void update() override;
    void dump_config() override;

    void set_I1_sensor(sensor::Sensor *s) { i1sensor = s; }
    void set_I2_sensor(sensor::Sensor *s) { i2sensor = s; }
    void set_I3_sensor(sensor::Sensor *s) { i3sensor = s; }
    

  protected:

    sensor::Sensor *i1sensor;
    sensor::Sensor *i2sensor;
    sensor::Sensor *i3sensor;

    char messagedata[SOLIS_S5_SERIAL_BUFFER_LEN] = {0};
    uint8_t messagelength = 0;
    volatile uint8_t sensorupdateprogress = 0;

};

} // namespace fogymero_dal
} // namespace esphome
