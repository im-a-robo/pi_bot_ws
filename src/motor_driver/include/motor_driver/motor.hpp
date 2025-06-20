#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <cstdint>

#include "motor_driver/pwm_driver.hpp"

enum class Command { FORWARD, BACKWARD, BREAK, RELEASE };

class Motor {
   private:
    PWM pwm_controller;
    uint8_t motor_channel;

    uint8_t pwm, in1, in2 = 0;

   public:
    Motor(PWM pwm_controller, int motor_channel);

    // motor functions
    void set_power(int pwr);
    void stop();
    void set_direction(Command cmd);
};

#endif
