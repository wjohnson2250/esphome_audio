#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "esphome/components/i2s_audio/i2s_audio.h"
#include <cmath>

namespace esphome {
namespace db_sound_meter {

class DBSoundMeterSink : public i2s_audio::AudioSink {
 public:
  explicit DBSoundMeterSink(sensor::Sensor *parent) : parent_(parent) {}

  void write(audio_frame_t *frame) override {
    if (frame == nullptr)
      return;

    const int16_t *data = reinterpret_cast<const int16_t *>(frame->data);
    size_t samples = frame->samples * frame->channels;

    float square_sum = 0.0f;
    for (size_t i = 0; i < samples; i++) {
      float sample = data[i] / 32768.0f;
      square_sum += sample * sample;
    }

    float rms = std::sqrt(square_sum / samples);
    float db = 20.0f * std::log10(rms + 1e-6f);

    parent_->publish_state(db);
  }

 protected:
  sensor::Sensor *parent_;
};

class DBSoundMeter : public sensor::Sensor, public Component {
 public:
  void set_i2s_audio_parent(i2s_audio::I2SAudioComponent *parent) { parent_ = parent; }

  void setup() override {
    sink_ = new DBSoundMeterSink(this);
    if (parent_ != nullptr) {
      parent_->add_sink(sink_);
    }
  }

  void loop() override {
    // Nothing needed here; all handled in sink's write()
  }

 protected:
  i2s_audio::I2SAudioComponent *parent_{nullptr};
  DBSoundMeterSink *sink_{nullptr};
};

}  // namespace db_sound_meter
}  // namespace esphome
