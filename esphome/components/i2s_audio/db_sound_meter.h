#pragma once

#include "esphome/components/sensor/sensor.h"
#include "i2s_audio.h"

namespace esphome {
namespace i2s_audio {

class DBSoundMeter : public sensor::Sensor, public Component {
 public:
  void set_i2s_audio_parent(I2SAudioComponent *parent) { parent_ = parent; }
  void loop() override;

 protected:
  I2SAudioComponent *parent_;
};

}  // namespace i2s_audio
}  // namespace esphome
