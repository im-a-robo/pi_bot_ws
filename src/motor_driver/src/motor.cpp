#include "motor_driver/motor.hpp"

#include <algorithm>

Motor::Motor(PWM pwm_controller, int motor_channel) : pwm_controller(pwm_controller) {
    this->motor_channel = motor_channel;

    switch (this->motor_channel) {
        case 0:
            this->pwm = 8;
            this->in2 = 9;
            this->in1 = 10;
            break;
        case 1:
            this->pwm = 13;
            this->in2 = 12;
            this->in1 = 11;
            break;
        case 2:
            this->pwm = 2;
            this->in2 = 3;
            this->in1 = 4;
            break;
        case 3:
            this->pwm = 7;
            this->in2 = 6;
            this->in1 = 5;
            break;
        default:
            std::cerr << "MotorHAT Motor must be between 1 and 4 inclusive" << std::endl;
            break;
    }
}

// pwr is on the scale of -100% to 100%
void Motor::set_power(int pwr) {
    uint16_t pwm_off = std::clamp(pwr, -100, 100) / 100 * 4096;

    this->pwm_controller.set_pwm(this->pwm, 0, pwm_off);
}

void Motor::stop() {
    this->pwm_controller.set_pwm(this->pwm, 0, 0);
}

void Motor::set_direction(Command cmd) {
    switch (cmd) {
        case Command::FORWARD:
            this->in1 = break;
    }
}
