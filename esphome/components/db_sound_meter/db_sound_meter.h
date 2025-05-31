#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "esphome/components/i2s_audio/i2s_audio.h"

namespace esphome {
namespace db_sound_meter {

class DBSoundMeter : public sensor::Sensor, public Component, public i2s_audio::AudioSink {
 public:
  void set_i2s_audio_parent(i2s_audio::I2SAudioComponent *parent) { parent_ = parent; }
  void setup() override;
  void write(audio_frame_t *frame) override;

 protected:
  i2s_audio::I2SAudioComponent *parent_{nullptr};
};

}  // namespace db_sound_meter
}  // namespace esphome
