import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID, CONF_MOTOR
from . import wemos_motor_ns, WemosMotor

DEPENDENCIES = ['wemos_motor']

WemosMotorOutput = wemos_motor_ns.class_('WemosMotorOutput', output.FloatOutput)

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(WemosMotorOutput),
    cv.Required(CONF_MOTOR): cv.use_id(WemosMotor),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await output.register_output(var, config)
    motor = await cg.get_variable(config[CONF_MOTOR])
    cg.add(var.set_motor(motor))
