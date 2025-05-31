#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "esphome/components/i2s_audio/i2s_audio_microphone.h"

namespace esphome {
namespace db_sound_meter {

class DBSoundMeter : public sensor::Sensor, public Component {
 public:
  void setup() override;

  // Register the callback with microphone
  void register_callback(i2s_audio::I2SAudioMicrophone *mic);

 protected:
  void on_audio_data(const std::vector<uint8_t> &data);
};

}  // namespace db_sound_meter
}  // namespace esphome
