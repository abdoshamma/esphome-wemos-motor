import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_ADDRESS, CONF_FREQUENCY

DEPENDENCIES = ['i2c']

wemos_motor_ns = cg.esphome_ns.namespace('wemos_motor')
WemosMotor = wemos_motor_ns.class_('WemosMotor', cg.Component)

CONF_MOTOR = "motor"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(WemosMotor),
    cv.Required(CONF_ADDRESS): cv.i2c_address,
    cv.Required(CONF_MOTOR): cv.int_range(min=0, max=1),
    cv.Optional(CONF_FREQUENCY, default=1000): cv.uint32_t,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    cg.add(var.set_address(config[CONF_ADDRESS]))
    cg.add(var.set_motor(config[CONF_MOTOR]))
    cg.add(var.set_frequency(config[CONF_FREQUENCY]))
