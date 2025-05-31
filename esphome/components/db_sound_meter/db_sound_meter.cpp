#include "db_sound_meter.h"
#include "esphome/core/log.h"
#include <cmath>

namespace esphome {
namespace db_sound_meter {

static const char *TAG = "db_sound_meter";

void DBSoundMeter::setup() {
  // Nothing special here; callback registration happens separately
}

void DBSoundMeter::register_callback(i2s_audio::I2SAudioMicrophone *mic) {
  // Register lambda as callback
  mic->add_data_callback([this](const std::vector<uint8_t> &data) { this->on_audio_data(data); });
}

void DBSoundMeter::on_audio_data(const std::vector<uint8_t> &data) {
  size_t sample_count = data.size() / 2;
  if (sample_count == 0)
    return;

  const int16_t *samples = reinterpret_cast<const int16_t *>(data.data());

  float square_sum = 0.0f;
  for (size_t i = 0; i < sample_count; i++) {
    float sample = samples[i] / 32768.0f;  // Normalize
    square_sum += sample * sample;
  }
  float rms = std::sqrt(square_sum / sample_count);
  float db = 20.0f * std::log10(rms + 1e-6f);

  this->publish_state(db);
  ESP_LOGD(TAG, "Sound level: %.2f dB", db);
}

}  // namespace db_sound_meter
}  // namespace esphome
