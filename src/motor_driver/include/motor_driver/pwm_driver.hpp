#ifndef PWM_DRIVER_HPP
#define PWM_DRIVER_HPP

#include <sys/types.h>

#include <cstdint>

#include "i2c_comm_cpp/i2c_utils.hpp"

class PWM {
   private:
    // registers/etc.
    const int MODE1_ = 0x00;
    const int MODE2_ = 0x01;
    const int SUBADR1_ = 0x02;
    const int SUBADR2_ = 0x03;
    const int SUBADR3_ = 0x04;
    const int PRESCALE_ = 0xFE;
    const int LED0_ON_L_ = 0x06;
    const int LED0_ON_H_ = 0x07;
    const int LED0_OFF_L_ = 0x08;
    const int LED0_OFF_H_ = 0x09;
    const int ALL_LED_ON_L_ = 0xFA;
    const int ALL_LED_ON_H_ = 0xFB;
    const int ALL_LED_OFF_L_ = 0xFC;
    const int ALL_LED_OFF_H_ = 0xFD;

    // bits
    const int RESTART_ = 0x80;
    const int SLEEP_ = 0x10;
    const int ALLCALL_ = 0x01;
    const int INVRT_ = 0x10;
    const int OUTDRV_ = 0x04;

    I2CDevice i2c;

   public:
    PWM(int i2c_addr);
    static void software_reset();
    void set_pwm_freq(const int freq);
    void set_pwm(u_int8_t pin, uint16_t on, uint16_t off);
    void set_all_pwm(uint16_t on, uint16_t off);
};

#endif
