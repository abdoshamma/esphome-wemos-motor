#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/output/float_output.h"  // Add this include
#include "Wire.h"

namespace esphome {
namespace wemos_motor {

#define _MOTOR_A 0
#define _MOTOR_B 1
#define _SHORT_BRAKE 0
#define _CCW 1
#define _CW 2
#define _STOP 3
#define _STANDBY 4

class WemosMotor : public Component {
public:
  WemosMotor(uint8_t address, uint8_t motor, uint32_t freq);
  void setup() override;
  void setfreq(uint32_t freq);
  void setmotor(uint8_t dir, float pwm_val);

protected:
  uint8_t _address;
  uint8_t _motor;
  uint32_t _freq;
};

// Add the output class here
class WemosMotorOutput : public output::FloatOutput {
 public:
  void set_motor(WemosMotor *motor) { motor_ = motor; }
  void write_state(float state) override {
    if (state > 0) {
      motor_->setmotor(_CW, state * 100);
    } else {
      motor_->setmotor(_STOP, 0);
    }
  }
 protected:
  WemosMotor *motor_;
};

}  // namespace wemos_motor
}  // namespace esphome
