#include "custom_i2s_sensor.h"
#include <cmath>

namespace esphome {
namespace custom_i2s {

void CustomI2SSensor::setup() {
  // Set polling interval (e.g., 500ms)
  this->set_update_interval(500);  // milliseconds
}

void CustomI2SSensor::update() {
  const size_t samples = 1024;
  int32_t sample;
  float sum_sq = 0;
  size_t count = 0;

  for (size_t i = 0; i < samples; i++) {
    if (component_->read(&sample)) {
      float f = sample / 32768.0f;  // Normalize 16-bit PCM
      sum_sq += f * f;
      count++;
    }
  }

  if (count > 0) {
    float rms = sqrtf(sum_sq / count);
    float db = 20.0f * log10(rms + 1e-9f);  // Avoid log(0)
    this->publish_state(db);
  } else {
    ESP_LOGW("custom_i2s_sensor", "No I2S samples available.");
  }
}

}  // namespace custom_i2s
}  // namespace esphome
