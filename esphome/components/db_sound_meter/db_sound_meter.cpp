#include "db_sound_meter.h"
#include "esphome/core/log.h"
#include <cmath>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static inline uint32_t millis() { return (uint32_t) (xTaskGetTickCount() * portTICK_PERIOD_MS); }

namespace esphome {
namespace db_sound_meter {

static const char *TAG = "db_sound_meter";

void DBSoundMeter::setup() { this->last_update_ = millis(); }

void DBSoundMeter::loop() {
  uint32_t now = millis();
  if (now - this->last_update_ < this->update_interval_) {
    return;
  }
  this->last_update_ = now;

  const int16_t *buffer = parent_->get_buffer();
  size_t length = parent_->get_buffer_length();
  if (buffer == nullptr || length == 0)
    return;

  float square_sum = 0;
  for (size_t i = 0; i < length; i++) {
    float sample = buffer[i] / 32768.0f;
    square_sum += sample * sample;
  }

  float rms = sqrtf(square_sum / length);
  float db = 20.0f * log10f(rms + 1e-6f);

  this->publish_state(db);
}

}  // namespace db_sound_meter
}  // namespace esphome
