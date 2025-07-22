#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <cstdint>
#include <iostream>

class MotorHat;

enum class Command { FORWARD, BACKWARD, BREAK, RELEASE };

class Motor {
   private:
    MotorHat* hat;
    uint8_t motor_channel;

    uint8_t pwm, in1, in2 = 0;

   public:
    Motor();
    Motor(MotorHat* hat, int motor_channel);

    // motor functions
    void set_power(int pwr);
    void stop();
    void set_direction(Command cmd);
};

#endif
