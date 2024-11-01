#include "wemos_motor.h"

namespace esphome {
namespace wemos_motor {

WemosMotor::WemosMotor(uint8_t address, uint8_t motor, uint32_t freq) {
  _address = address;
  _motor = motor;
  _freq = freq;
}

void WemosMotor::setup() {
  Wire.begin();
  setfreq(_freq);
}

void WemosMotor::setfreq(uint32_t freq) {
  Wire.beginTransmission(_address);
  Wire.write(((byte)(freq >> 16)) & (byte)0x0f);
  Wire.write((byte)(freq >> 16));
  Wire.write((byte)(freq >> 8));
  Wire.write((byte)freq);
  Wire.endTransmission();
}

void WemosMotor::setmotor(uint8_t dir, float pwm_val) {
  uint16_t _pwm_val = uint16_t(pwm_val * 100);
  if (_pwm_val > 10000)
    _pwm_val = 10000;

  Wire.beginTransmission(_address);
  Wire.write(_motor | (byte)0x10);
  Wire.write(dir);
  Wire.write((byte)(_pwm_val >> 8));
  Wire.write((byte)_pwm_val);
  Wire.endTransmission();
}

}  // namespace wemos_motor
}  // namespace esphome
