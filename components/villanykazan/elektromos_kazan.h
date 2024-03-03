#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
//#include "esphome/components/text_sensor/text_sensor.h"
//#include "esphome/components/binary_sensor/binary_sensor.h"


namespace esphome {
namespace elektromos_kazan {

class ElwktromosKazanComponent : public PollingComponent {
  public:

    void setup() override;
    void loop() override;
    void update() override;
    void dump_config() override;

    void set_i1_sensor(sensor::Sensor *s) { i1sensor = s; }
    void set_i2_sensor(sensor::Sensor *s) { i2sensor = s; }
    void set_i3_sensor(sensor::Sensor *s) { i3sensor = s; }
    

  protected:

    sensor::Sensor *i1sensor;
    sensor::Sensor *i2sensor;
    sensor::Sensor *i3sensor;

    char messagedata[300] = {0};
    uint8_t messagelength = 0;
    volatile uint8_t sensorupdateprogress = 0;
    bool _7Buzenet_kell = false;

};

} // namespace elektromos_kazan
} // namespace esphome

