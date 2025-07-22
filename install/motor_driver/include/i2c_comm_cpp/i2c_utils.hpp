#ifndef I2C_UTILS_HPP
#define I2C_UTILS_HPP

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h> /* For open(), */

#include <cstdint>
#include <iostream>

#include "i2c-dev.h"

class I2CDevice {
   private:
    int file;             // used to access the open I2C file
    int adapter_num = 1;  // change per I2C master device
    char filename[20];    // the linux I2C interface/socket filename

    int addr;  // address of the slave device

   public:
    I2CDevice(int addr);

    void send_data(uint8_t data);
    void write_data(uint8_t reg, uint8_t length, const uint8_t data[]);
    void write_byte(uint8_t reg, uint8_t data);
    void recive_data(uint8_t *data);
    int read_byte(uint8_t reg);
    int read_u_byte(uint8_t reg);
    void read_data(uint8_t reg, uint8_t data[]);
};

#endif
