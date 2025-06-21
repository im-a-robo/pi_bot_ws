
#include "motor_driver/motor_hat.hpp"

#include <memory>

MotorHat::MotorHat(int i2c_addr, int freq) : pwm(i2c_addr) {
    // setup motors
    for (int i = 0; i < 4; i++) {
        motors[i] = std::make_shared<Motor>(this, i);
    }
    this->pwm.set_pwm_freq(freq);
}

void MotorHat::set_pin(const uint8_t pin, uint8_t val) {
    uint16_t on = val ? 4096 : 0;
    uint16_t off = val ? 0 : 4096;
    this->pwm.set_pwm(pin, on, off);
}

std::shared_ptr<Motor> MotorHat::get_motor(const uint8_t num) {
    return motors.at(num - 1);
}
