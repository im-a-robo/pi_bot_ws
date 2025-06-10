#ifndef MOTOR_HAT_HPP
#define MOTOR_HAT_HPP

#include <i2c_comm_cpp/i2c_utils.hpp>

class enum

    class MotorHat {
        private : const int i2c_addr_ = 0x60;  // address of led pwm controller {1:A5(1):A[4:0](0)}
        I2CDevice hat = I2CDevice(i2c_addr_);

        public : MotorHat();

    };

#endif
