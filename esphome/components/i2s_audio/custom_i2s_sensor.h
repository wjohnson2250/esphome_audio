#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2s_audio/i2s_audio.h"

namespace esphome {
namespace custom_i2s {

class CustomI2SSensor : public sensor::Sensor, public PollingComponent {
 public:
  explicit CustomI2SSensor(i2s_audio::I2SAudioComponent *component) : component_(component) {} 

  void setup() override {}
  void update() override;

 protected:
 i2s_audio::I2SAudioComponent *component_;
};

}  // namespace custom_i2s
}  // namespace esphome
