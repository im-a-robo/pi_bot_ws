#ifndef MOTOR
#define MOTOR

#include "i2c_comm_cpp/i2c_utils.hpp"

class Motor {
   private:
    I2CDevice motor;

   public:
    Motor(int motor_addr);
};

#endif
