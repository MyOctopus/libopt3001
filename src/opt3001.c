/*
 * libopt3001 - OPT3001 ambient light sensor library
 *
 * Copyright (C) 2015 by Artur Wroblewski <wrobell@pld-linux.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef OPT3001_DEBUG
#define DEBUG_LOG(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define DEBUG_LOG(fmt, ...)
#endif

/* i2c file descriptor */
static int i2c_fd;

/*
 * Public API implementation.
 */

int opt3001_init(const char *f_dev, unsigned char address) {
    int r, i;

    if ((i2c_fd = open(f_dev, O_RDWR)) < 0)
        return -1;

    /* set the port options and set the address of the device */
    if (ioctl(i2c_fd, I2C_SLAVE, address) < 0)
        return -1;

    r = write(i2c_fd, (uint8_t[]) {0x01, 0x5c, 0x10}, 3);
    if (r != 3) {
        perror("opt3001 config error:");
        return -1;
    }

    return 0;
}

int opt3001_read(float *lux) {
    int r;
    uint8_t data[2];
    uint16_t raw;
    uint8_t exp;

    r = write(i2c_fd, (uint8_t[]) {0x00}, 1);
    if (r != 1) {
        perror("opt3001 command error:");
        return -1;
    }
    r = read(i2c_fd, data, 2);
    if (r != 2)
        return -1;

    raw = ((data[0] & 0x0f) << 8) + data[1];
    exp = data[0] >> 4;
    *lux = (1 << exp) * raw / 100.0;
    DEBUG_LOG("opt3001 data: [%x %x] = %.4f\n", data[0], data[1], *lux);
    return 0;
}

int opt3001_close() {
    close(i2c_fd);
}

/*
 * vim: sw=4:et:ai
 */
