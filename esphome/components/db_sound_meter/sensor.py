import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import UNIT_DECIBEL
from esphome.components.i2s_audio import I2SAudioMicrophone

db_sound_meter_ns = cg.esphome_ns.namespace('db_sound_meter')
DBSoundMeter = db_sound_meter_ns.class_('DBSoundMeter', cg.Component, sensor.Sensor)

CONF_MIC_ID = 'mic_id'

CONFIG_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_DECIBEL,
    icon='mdi:microphone',
    accuracy_decimals=1,
).extend({
    cv.Required(CONF_MIC_ID): cv.declare_id(I2SAudioMicrophone),  # Declare this as a reference ID to another component
    cv.GenerateID(): cv.declare_id(DBSoundMeter),
})

async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)

    mic_id = config[CONF_MIC_ID]
    mic = await cg.get_variable(mic_id)  # Pass string directly
    cg.add(var.register_callback(mic))
