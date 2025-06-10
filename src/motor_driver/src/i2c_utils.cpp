#include "i2c_comm_cpp/i2c_utils.hpp"

#include <i2c/smbus.h>

#include <cstdint>

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

void I2CDevice::send_data(uint8_t data) {
    int res = i2c_smbus_write_byte(file, data);
    if (res < 0) {
        std::cerr << "Could not send data error: " << res << std::endl;
    }
}

void I2CDevice::write_byte(uint8_t reg, uint8_t data) {
    int res = i2c_smbus_write_byte_data(file, reg, data);
    if (res < 0) {
        std::cerr << "Could not write byte data error: " << res << std::endl;
    }
}

void I2CDevice::write_data(uint8_t reg, uint8_t length, const uint8_t data[]) {
    int res = i2c_smbus_write_block_data(file, reg, length, data);
    if (res < 0) {
        std::cerr << "Could not write data error: " << res << std::endl;
    }
}

void I2CDevice::recive_data(uint8_t *data) {
    int res = i2c_smbus_read_byte(file);
    if (res < 0) {
        std::cerr << "Could not recive data error: " << res << std::endl;
    }
    *data = (uint8_t)res;
}

int I2CDevice::read_byte(uint8_t reg) {
    int res = i2c_smbus_read_byte_data(file, reg);
    if (res < 0) {
        std::cerr << "Could not read byte error: " << res << std::endl;
    }
    return res;
}

int I2CDevice::read_u_byte(uint8_t reg) {
    int res = i2c_smbus_read_byte_data(file, reg) & 0xFF;
    if (res < 0) {
        std::cerr << "Could not read byte error: " << res << std::endl;
    }
    return res;
}

void I2CDevice::read_data(uint8_t reg, uint8_t data[]) {
    int res = i2c_smbus_read_block_data(file, reg, data);
    if (res < 0) {
        std::cerr << "Could not read data error: " << res << std::endl;
    }
}
