import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import UNIT_DECIBEL

db_sound_meter_ns = cg.esphome_ns.namespace('db_sound_meter')
DBSoundMeter = db_sound_meter_ns.class_('DBSoundMeter', cg.Component, sensor.Sensor)

# Correctly declare mic_in as an ID object, not a string
MIC_ID = cg.ID('mic_in')

CONFIG_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_DECIBEL,
    icon='mdi:microphone',
    accuracy_decimals=1,
).extend({
    cv.GenerateID(): cv.declare_id(DBSoundMeter),
})

async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)

    # Use the ID object for the microphone instance
    mic = await cg.get_variable(MIC_ID)
    cg.add(var.register_callback(mic))
