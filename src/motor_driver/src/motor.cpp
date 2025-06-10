#include "motor_driver/motor.hpp"

Motor::Motor(int motor_channel) {
    this->motor_channel = motor_channel;
}

// pwr is on the scale of -100% to 100%
Motor::set_power(int pwr) {}
