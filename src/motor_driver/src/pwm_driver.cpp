#include "motor_driver/pwm_driver.hpp"

#include <chrono>
#include <cstdint>
#include <thread>

#include "i2c_comm_cpp/i2c_utils.hpp"

PWM::PWM(int i2c_addr) : i2c(i2c_addr) {
    this->set_all_pwm(0, 0);
    i2c.write_byte(this->MODE2_, this->OUTDRV_);
        i2c.write_byte(this->MODE1_, this->ALLCAL
        std::this_thread::sleep_for(std::chrono::milliseconds(
        uint8_t mode1 = i2c.read_u_byte(this->MODE1_);  // wait for ossil
        mode1 = mode1 & ~this->SLEEP_; // wake up pwm (reset the sleep bit)
        i2c.write_byte(this->MODE1_, mode1);  // wait for ossilator
        std::this_thread::sleep_for(std::chrono::milliseconds(
