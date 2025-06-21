#include "motor_driver/pwm_driver.hpp"

#include <sys/types.h>

#include <chrono>
#include <cstdint>
#include <thread>

#include "i2c_comm_cpp/i2c_utils.hpp"

PWM::PWM(int i2c_addr) : i2c(i2c_addr) {
    this->set_all_pwm(0, 0);
    i2c.write_byte(this->MODE2_, this->OUTDRV_);  //
    i2c.write_byte(this->MODE1_, this->ALLCALL_);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    uint8_t mode1 = i2c.read_u_byte(this->MODE1_);  // wait for ossilator
    mode1 = mode1 & ~this->SLEEP_;                  // wake up pwm (reset the sleep bit)
    i2c.write_byte(this->MODE1_, mode1);            // wait for ossilator
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

void PWM::software_reset() {
    I2CDevice general_call_i2c = I2CDevice(0x00);
    general_call_i2c.send_data(0x06);
}

void PWM::set_pwm_freq(const int freq) {
    float prescale_val = 25000000;
    prescale_val /= 4096;
    prescale_val /= freq;
    prescale_val -= 1.0;

    float prescale = std::floor(prescale_val + 0.5);

    int oldmode = i2c.read_u_byte(this->MODE1_);
    int newmode = (oldmode & 0x7F) | 0x10;

    this->i2c.write_byte(this->MODE1_, newmode);
    this->i2c.write_byte(this->PRESCALE_, int(std::floor(prescale)));
    this->i2c.write_byte(this->MODE1_, oldmode);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    this->i2c.write_byte(this->MODE1_, oldmode | 0x80);
}

void PWM::set_pwm(uint8_t channel, uint16_t on, uint16_t off) {
    this->i2c.write_byte(this->LED0_ON_L_ + 4 * channel, on & 0xFF);
    this->i2c.write_byte(this->LED0_ON_H_ + 4 * channel, on >> 8);
    this->i2c.write_byte(this->LED0_OFF_L_ + 4 * channel, off & 0xFF);
    this->i2c.write_byte(this->LED0_OFF_H_ + 4 * channel, off >> 8);
}

void PWM::set_all_pwm(uint16_t on, uint16_t off) {
    this->i2c.write_byte(this->ALL_LED_ON_L_, on & 0xFF);
    this->i2c.write_byte(this->ALL_LED_ON_H_, on >> 8);
    this->i2c.write_byte(this->ALL_LED_OFF_L_, off & 0xFF);
    this->i2c.write_byte(this->ALL_LED_OFF_H_, off >> 8);
}
