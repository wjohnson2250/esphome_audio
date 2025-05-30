#include "db_sound_meter.h"
#include "esphome/core/log.h"
#include <cmath>

namespace esphome {
namespace i2s_audio {

static const char *TAG = "db_sound_meter";

void DBSoundMeter::loop() {
  const int16_t *buffer = parent_->get_buffer();  // Get raw audio buffer
  size_t length = parent_->get_buffer_length();

  if (buffer == nullptr || length == 0)
    return;

  float square_sum = 0;
  for (size_t i = 0; i < length; i++) {
    float sample = buffer[i] / 32768.0f;  // Normalize to [-1, 1]
    square_sum += sample * sample;
  }

  float rms = sqrtf(square_sum / length);
  float db = 20.0f * log10f(rms + 1e-6f);  // Avoid log(0)

  this->publish_state(db);
}

}  // namespace i2s_audio
}  // namespace esphome
