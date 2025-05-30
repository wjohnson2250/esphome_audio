#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

namespace esphome {
namespace db_sound_meter {

class DBSoundMeter : public sensor::Sensor, public Component {
 public:
  void set_i2s_audio_parent(I2SAudioComponent *parent) { parent_ = parent; }
  void set_update_interval(uint32_t interval_ms) { this->update_interval_ = interval_ms; }
  void setup() override;
  void loop() override;

 protected:
  I2SAudioComponent *parent_{nullptr};
  uint32_t update_interval_{1000};
  uint32_t last_update_{0};
};

}  // namespace db_sound_meter
}  // namespace esphome
