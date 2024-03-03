#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
//#include "esphome/components/text_sensor/text_sensor.h"
//#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/core/log.h"
#include "elektromos_kazan.h"

namespace esphome {
namespace elektromos_kazan {

static const char *TAG = "Villanykazán: ";

void ElektromosKazanComponent::setup() {
  // nothing to do here
  
}

void ElektromosKazanComponent::loop() {

 
 uint16_t v = this->i1_mert;
 this->i1sensor->publish_state((float)v * 0.1f); 
  }



void ElektromosKazanComponent::update() {
  
    ESP_LOGV(TAG, "update lefutott");
   
  }


void ElektromosKazanComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "dump lefutott");
}

} // namespace fogymerodal
} // namespace esphome

