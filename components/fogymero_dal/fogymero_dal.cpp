#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
//#include "esphome/components/text_sensor/text_sensor.h"
//#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/log.h"
#include "fogymero_dal.h"

namespace esphome {
namespace fogymero_dal {

static const char *TAG = "fogymero_dal";

void FogymeroDalComponent::setup() {
  // nothing to do here
}

void FogymeroDalComponent::loop() {

if (Serial.available() <= 0) {  
Serial.write (0x10);
Serial.write (0x5B);
Serial.write (0xFE);
Serial.write (0x59);
Serial.write (0x16);  
delay(300);
  }
  
  

  if (this->sensorupdateprogress > 0) {
    switch (this->sensorupdateprogress) {
      case 3:
        if (this->i1sensor != nullptr) {
          uint16_t v = this->messagedata[1] + this->messagedata[2]*256;
          
          this->i1sensor->publish_state((float)v * 0.1f);
        }
        break;

      case 2:
        if (this->i2sensor != nullptr) {
          uint16_t v = this->messagedata[3] + this->messagedata[4]*256;
          this->i2sensor->publish_state((float)v * 0.1f);
        }
        break;

      case 1:
        if (this->i3sensor != nullptr) {
          uint16_t v = this->messagedata[5] + this->messagedata[6]*256;
          v=253;
          this->i3sensor->publish_state((float)v * 0.1f);
        }
        break;
      
    }
    this->sensorupdateprogress--;
  }

  static char buffer[300] = {0};
  static uint8_t index = 0;
  static uint8_t loopwait = 0;

  while (available()) {
    buffer[index] = read();
    index++;
    index%=300;
    loopwait = 0;
  }
  if (index > 0) {
    loopwait++;
  }
  /*
  if (loopwait > SOLIS_S5_LOOP_WAIT) { // some time has passed without receiving another character. this should be the end of a message.
    ESP_LOGV(TAG, "message recieved len=%d", index);
    if (buffer[0] == 126) { // message starts with the right preamble
      uint8_t msglen = buffer[3];
      if (index == msglen + 5) { // messasge has correct length
        uint8_t csum = 0;
        for (uint8_t i = 1; i < msglen+4; i++) { // csum after preamble, before tx csum
          csum += buffer[i];
        }
        if (csum == buffer[msglen+4]) { // checksum ok
          if ((buffer[2] == 161) && (msglen == 80)) { // inverter response
            memcpy(this->messagedata,buffer,SOLIS_S5_SERIAL_BUFFER_LEN); // copy message for processing on next update cycle
            this->messagelength = index; // length > 0 indicates the message data has been updated / ready for parsing
            ESP_LOGD(TAG, "inverter data received");
          } else if ((buffer[2] == 193) && (msglen == 40)) { // inverter config response
            ESP_LOGD(TAG, "inverter config response received");
          }
        } else {
          ESP_LOGV(TAG, "message checksum fail; discarding. csum = 0x%02X, check = 0x%02X", buffer[msglen+4], csum);
        }
      } else if ((msglen == 0) && (index == 55)) { // wifi stick command
        ESP_LOGD(TAG, "wifi stick command received; ignoring");
      } else {
        ESP_LOGV(TAG, "message insufficient length (requested: %d, received: %d); discarding", msglen+5, index);
      }
    } else {
      ESP_LOGV(TAG, "message received, invalid start character");
    }
    */
    // reset message, ready for next one
    loopwait = 0;
    index = 0;
  }



void FogymeroDalComponent::update() {
  if (this->messagelength > 0) { // if there's a message pending
    ESP_LOGV(TAG, "processing latest message");
    this->messagelength = 0; // indicate message is parsed   
    this->sensorupdateprogress = 3; // start to update sensors
  } else {
    ESP_LOGV(TAG, "no data received");
    this->messagelength=1; 
  }
}


void FogymeroDalComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Fogymérő DAL");
}

} // namespace fogymerodal
} // namespace esphome
