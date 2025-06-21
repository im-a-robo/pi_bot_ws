#ifndef MOTOR_HAT_HPP
#define MOTOR_HAT_HPP

#include <cstdint>
#include <memory>
#include <vector>

#include "i2c_comm_cpp/i2c_utils.hpp"
#include "motor_driver/motor.hpp"
#include "motor_driver/pwm_driver.hpp"

class MotorHat {
   private:
    std::vector<std::shared_ptr<Motor>> motors;

   public:
    MotorHat(int i2c_addr, int freq);

    PWM pwm;
    void set_pin(const uint8_t pin, uint8_t val);
    std::shared_ptr<Motor> get_motor(const uint8_t num);
};

#endif
