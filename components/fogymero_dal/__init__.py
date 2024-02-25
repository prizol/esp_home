import re
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import (
    CONF_ID,
    CONF_RECEIVE_TIMEOUT,
    CONF_UPDATE_INTERVAL,
)

fogymero_dal_ns = cg.esphome_ns.namespace("fogymero_dal")
FogymeroDalComponent = fogymero_dal_ns.class_(
    "FogymeroDalComponent", cg.Component, uart.UARTDevice

CODEOWNERS = ["@prizol"]

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["sensor", "text_sensor", "switch", "binary_sensor"]

CONF_I1 = "aram_1"
CONF_I2 = "aram_2"
CONF_I3 = "aram_3"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(FogymeroDalComponent),

    cv.Optional(CONF_I1):
        sensor.sensor_schema(device_class=DEVICE_CLASS_CURRENT,unit_of_measurement=UNIT_AMPERE,accuracy_decimals=1,state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_I2):
        sensor.sensor_schema(device_class=DEVICE_CLASS_CURRENT,unit_of_measurement=UNIT_AMPERE,accuracy_decimals=1,state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_I3):
        sensor.sensor_schema(device_class=DEVICE_CLASS_CURRENT,unit_of_measurement=UNIT_AMPERE,accuracy_decimals=1,state_class=STATE_CLASS_MEASUREMENT).extend(),
}).extend(cv.polling_component_schema('60s')).extend(uart.UART_DEVICE_SCHEMA)


)

