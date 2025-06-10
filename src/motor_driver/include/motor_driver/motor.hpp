#ifndef MOTOR
#define MOTOR

#include <cstdint>

#include "i2c_comm_cpp/i2c_utils.hpp"

class Motor {
   private:
    I2CDevice pwm_controller =
        I2CDevice(0x60);  // address of led pwm controller {1:A5(1):A[4:0](0)}

    uint8_t motor_channel;

   public:
    Motor(int motor_channel);

    // motor functions
    void set_power(int pwr);
    void stop();
};

#endif
