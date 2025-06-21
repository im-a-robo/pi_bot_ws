#include "motor_driver/motor.hpp"

#include <algorithm>

#include "motor_driver/motor_hat.hpp"

Motor::Motor(MotorHat* hat, int motor_channel) : hat(hat) {
    this->motor_channel = motor_channel;
    switch (this->motor_channel) {
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
    pwr = std::clamp(pwr, -100, 100);

    if (pwr < 0) {
        set_direction(Command::BACKWARD);
    } else {
        set_direction(Command::FORWARD);
    }

    uint16_t pwm_off = std::abs(pwr) / 100 * 4096;

    this->hat->pwm.set_pwm(this->pwm, 0, pwm_off);
}

void Motor::stop() {
    this->hat->pwm.set_pwm(this->pwm, 0, 0);
}

void Motor::set_direction(Command cmd) {
    switch (cmd) {
        case Command::FORWARD:
            hat->set_pin(this->in1, 1);
            hat->set_pin(this->in2, 0);
            break;
        case Command::BACKWARD:
            hat->set_pin(this->in1, 0);
            hat->set_pin(this->in2, 1);
            break;
        case Command::RELEASE:
            hat->set_pin(this->in1, 0);
            hat->set_pin(this->in2, 0);
            break;
        case Command::BREAK:
            hat->set_pin(this->in1, 1);
            hat->set_pin(this->in2, 1);
            break;
    }
}
