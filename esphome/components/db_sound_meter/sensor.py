import esphome.config_validation as cv
from esphome import automation
from esphome.core import coroutine
from esphome.const import CONF_ID, CONF_NAME, UNIT_DECIBEL
import esphome.codegen as cg
from esphome.components import sensor, i2s_audio

CONF_I2S_AUDIO_ID = "i2s_audio_id"
CONF_UPDATE_INTERVAL = "update_interval"

db_sound_meter_ns = cg.esphome_ns.namespace("db_sound_meter")
DBSoundMeter = db_sound_meter_ns.class_("DBSoundMeter", cg.Component, sensor.Sensor)

CONFIG_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_DECIBEL,
    icon="mdi:microphone",
    accuracy_decimals=1,
).extend({
    cv.GenerateID(): cv.declare_id(DBSoundMeter),
    cv.Required(CONF_I2S_AUDIO_ID): cv.use_id(i2s_audio.I2SAudioComponent),
    cv.Optional(CONF_UPDATE_INTERVAL, default="1s"): cv.positive_time_period_milliseconds,
})

async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    parent = await cg.get_variable(config[CONF_I2S_AUDIO_ID])
    cg.add(var.set_i2s_audio_parent(parent))
    if CONF_UPDATE_INTERVAL in config:
        cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
