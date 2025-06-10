#include "motor_driver/pwm_driver.hpp"

#include <sys/types.h>

#include <chrono>
#include <cmath>
#include <cstdint>
#include <ratio>
#include <thread>

#include "i2c_comm_cpp/i2c_utils.hpp"

PWM::PWM(int i2c_addr) : i2c(i2c_addr) {
    this->set_all_pwm(0, 0);
    i2c.write_byte(this->MODE2_, this->OUTDRV_);  //
    i2c.write_byte(this->MODE1_, this->ALLCALL_);
    std::this_thread::sleep_for(std::chrono::microseconds(500));
    uint8_t mode1 = i2c.read_u_byte(this->MODE1_);  // wait for ossilator
    mode1 = mode1 & ~this->SLEEP_;                  // wake up pwm (reset the sleep bit)
    i2c.write_byte(this->MODE1_, mode1);            // wait for ossilator
    std::this_thread::sleep_for(std::chrono::microseconds(500));
}

void PWM::set_pwm_freq(const int freq) {
    int prescale_val = 25000000.0;  // 25MHz
    prescale_val /= 4096.0;         // 12-bit
    prescale_val /= float(freq);
    prescale_val -= 1.0;
    prescale_val = std::floor(prescale_val + 0.5);

    uint8_t old_mode = i2c.read_u_byte(this->MODE1_);
    uint8_t sleep_mode = old_mode | this->SLEEP_;
    i2c.write_byte(this->MODE1_, sleep_mode);
    i2c.write_byte(this->PRESCALE_, prescale_val);
    i2c.write_byte(this->MODE1_, old_mode);

    std::this_thread::sleep_for(std::chrono::microseconds(500));
    i2c.write_byte(this->MODE1_, this->RESTART_);
}

void PWM::set_pwm(uint8_t pin, uint16_t on, uint16_t off) {
    i2c.write_byte(this->LED0_OFF_L_ + 4 * pin, on & 0xFF);
    i2c.write_byte(this->LED0_OFF_H_ + 4 * pin, on >> 8);
    i2c.write_byte(this->LED0_OFF_L_ + 4 * pin, off & 0xFF);
    i2c.write_byte(this->LED0_OFF_H_ + 4 * pin, off >> 8);
}

void PWM::set_all_pwm(uint16_t on, uint16_t off) {
    i2c.write_byte(this->ALL_LED_ON_L_, on & 0xFF);
    i2c.write_byte(this->ALL_LED_ON_H_, on >> 8);
    i2c.write_byte(this->ALL_LED_OFF_L_, off & 0xFF);
    i2c.write_byte(this->ALL_LED_OFF_H_, off >> 8);
}
