#include "i2c_comm_cpp/i2c_utils.hpp"

#include <cstdio>
#include <iostream>

I2CDevice::I2CDevice(int addr) {
    snprintf(this->filename, 19, "/dev/i2c-%d", adapter_num);
    this->file = open(this->filename, O_RDWR);
    if (file < 0) {
        std::cerr << "Error opening file " << filename << " while attempting to access I2C Bus"
                  << std::endl;
        exit(1);
    }

    this->addr = addr;

    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        std::cerr << "Erro accessing slave device at address " << addr << std::endl;
    }

    std::cout << "Success connecting to I2C device at addr" << this->addr << std::endl;
}
