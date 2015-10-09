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

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "opt3001.h"

int main() {
    float lux;
    time_t t;
    int r;

    r = opt3001_init("/dev/i2c-1", 0x45);
    if (r != 0) {
        perror("cannot initialize i2c device: ");
        return -1;
    }

    while (1) {
        time(&t);
        r = opt3001_read(&lux);
        printf("%d: %.4f (err=%d)\n", t, lux, r);
        sleep(1);
    }
    return 0;
}

