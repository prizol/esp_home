import re
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import (
    CONF_ID,
    CONF_RECEIVE_TIMEOUT,
    CONF_UPDATE_INTERVAL,
)

CODEOWNERS = ["@prizol"]

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["sensor", "text_sensor", "switch", "binary_sensor"]

fogymero_dal_ns = cg.esphome_ns.namespace("fogymero_dal")
FogymeroDalComponent = fogymero_dal_ns.class_(
    "FogymeroDalComponent", cg.Component, uart.UARTDevice
)

