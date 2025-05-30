import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, i2s_audio
from esphome.const import CONF_ID, CONF_NAME, UNIT_DECIBEL

CONF_I2S_AUDIO_ID = "i2s_audio_id"

db_sound_meter_ns = cg.esphome_ns.namespace("i2s_audio")
DBSoundMeter = db_sound_meter_ns.class_("DBSoundMeter", cg.Component, sensor.Sensor)

CONFIG_SCHEMA = sensor.sensor_schema(UNIT_DECIBEL, "mdi:microphone", 1).extend({
    cv.GenerateID(): cv.declare_id(DBSoundMeter),
    cv.GenerateID(CONF_I2S_AUDIO_ID): cv.use_id(i2s_audio.I2SAudioComponent),
})

async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    parent = await cg.get_variable(config[CONF_I2S_AUDIO_ID])
    cg.add(var.set_i2s_audio_parent(parent))
