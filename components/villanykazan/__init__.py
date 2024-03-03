import re
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor,uart
from esphome.const import *

fogymero_dal_ns = cg.esphome_ns.namespace("elektromos_kazan")
FogymeroDalComponent = elektromos_kazan_ns.class_(
    "ElektromosKazanComponent", cg.Component, uart.UARTDevice)

CODEOWNERS = ["@prizol"]

AUTO_LOAD = ["sensor", "text_sensor", "switch", "binary_sensor"]

CONF_I1 = "aram_1"
CONF_I2 = "aram_2"
CONF_I3 = "aram_3"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ElektromosKazanComponent),
    cv.Optional(CONF_I1): sensor.sensor_schema(UNIT_AMPERE, ICON_FLASH, 2),
    cv.Optional(CONF_I2): sensor.sensor_schema(UNIT_AMPERE, ICON_FLASH, 2),
    cv.Optional(CONF_I13 sensor.sensor_schema(UNIT_AMPERE, ICON_FLASH, 2),

}).extend(cv.polling_component_schema('60s'))

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)
    
    if CONF_I1 in config:
        conf = config[CONF_I1]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_i1_sensor(sens))

    if CONF_I2 in config:
        conf = config[CONF_I2]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_i2_sensor(sens))

    if CONF_I3 in config:
        conf = config[CONF_I3]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_i3_sensor(sens))
    
