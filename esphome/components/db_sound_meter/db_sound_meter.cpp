#include "db_sound_meter.h"
#include "esphome/core/log.h"
#include <cmath>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static inline uint32_t millis() { return (uint32_t) (xTaskGetTickCount() * portTICK_PERIOD_MS); }

namespace esphome {
namespace db_sound_meter {

static const char *TAG = "db_sound_meter";

void DBSoundMeter::setup() {
  if (parent_ != nullptr) {
    parent_->add_sink(this);
  }
}

void DBSoundMeter::write(audio_frame_t *frame) {
  if (!frame)
    return;

  const int16_t *data = reinterpret_cast<const int16_t *>(frame->data);
  size_t samples = frame->samples * frame->channels;

  float square_sum = 0.0f;
  for (size_t i = 0; i < samples; i++) {
    float sample = data[i] / 32768.0f;
    square_sum += sample * sample;
  }

  float rms = sqrtf(square_sum / samples);
  float db = 20.0f * log10f(rms + 1e-6f);

  this->publish_state(db);

  ESP_LOGD(TAG, "Sound level: %.2f dB", db);
}

}  // namespace db_sound_meter
}  // namespace esphome
