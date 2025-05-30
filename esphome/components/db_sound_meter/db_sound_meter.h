#pragma once

#include "esphome/components/i2s_audio/i2s_audio.h"
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace db_sound_meter {

class DBSoundMeter : public sensor::Sensor, public Component {
 public:
  void set_i2s_audio_parent(i2s_audio::I2SAudioComponent *parent) { parent_ = parent; }
  void set_update_interval(uint32_t interval_ms) { this->update_interval_ = interval_ms; }
  void setup() override;
  void loop() override;

 protected:
  i2s_audio::I2SAudioComponent *parent_{nullptr};
  uint32_t update_interval_{1000};
  uint32_t last_update_{0};
};

}  // namespace db_sound_meter
}  // namespace esphome
