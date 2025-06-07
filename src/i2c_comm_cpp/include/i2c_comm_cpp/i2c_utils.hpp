#ifndef I2C_UTILS_HPP
#define I2C_UTILS_HPP

#include <fcntl.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h> /* For open(), */

class I2CDevice {
   private:
    int file;             // used to access the open I2C file
    int adapter_num = 1;  // change per master device
    char filename[20];    // the linux I2C interface/socket filename

    int addr;  // address of the slave device

   public:
    I2CDevice(int addr);
};

#endif
