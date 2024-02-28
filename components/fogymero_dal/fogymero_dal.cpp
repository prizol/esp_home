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

if (available() <= 0) {  
  if (this->_7Buzenet_kell) {
    write (0x10);
    write (0x7B);
    write (0xFE);
    write (0x79);
    write (0x16);
     }
  else
    {
write (0x10);
write (0x5B);
write (0xFE);
write (0x59);
write (0x16); 
      }
delay(1000);
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
          uint16_t v = this->messagedata[81] + this->messagedata[82]*256;
          this->i3sensor->publish_state((float)v * 0.01f);
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
    ESP_LOGV(TAG, "message recieved len=%d", index);
    ESP_LOGV(TAG, "message byte 80=%d", buffer[80]);
        ESP_LOGV(TAG, "message byte 81=%d", buffer[81]);
        ESP_LOGV(TAG, "message byte 82=%d", buffer[82]);
        ESP_LOGV(TAG, "message byte 83=%d", buffer[83]);
        ESP_LOGV(TAG, "message byte 84=%d", buffer[84]);
  }
  
  if (loopwait > 0) { 
    if (buffer[0] == 0x68) { // message starts with the right preamble
      //ESP_LOGV(TAG, "A jó ID-jú válasz jött");
      if (buffer[1] == 0x74) { //a kettes számú válasz jött
        //ESP_LOGV(TAG, "A második válasz jött");

        memcpy(this->messagedata,buffer,150); // copy message for processing on next update cycle
            this->messagelength = index; // length > 0 indicates the message data has been updated / ready for parsing
       
      
      } else {
        ESP_LOGV(TAG, "Nem a jó válasz jött");
        if (this->_7Buzenet_kell) {
          this->_7Buzenet_kell=false;
         }
        else
         {
          this->_7Buzenet_kell=true;
        }
      }
    } else {
      ESP_LOGV(TAG, "message received, invalid start character");
      if (this->_7Buzenet_kell) {
          this->_7Buzenet_kell=false;
         }
        else
         {
          this->_7Buzenet_kell=true;
        }
    }
     }
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
   
  }
}


void FogymeroDalComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Fogymérő DAL");
}

} // namespace fogymerodal
} // namespace esphome
