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

#if !defined (_OPT3001_H_)
#define _OPT3001_H_

/*!
 * \brief Initialize OPT3001 sensor.
 *
 * Initialize I2C bus and configure sensor.
 *
 * \param f_dev I2C device filename, i.e. /dev/i2c-0.
 * \param address I2C device address, i.e. 0x77.
 */
int opt3001_init(const char *f_dev, unsigned char address);

/*!
 * \brief Read lux information from OPT3001 sensor.
 *
 * \param lux Lux information.
 */
int opt3001_read(float *lux);

/*!
 * \brief Release OPT3001 sensor resources.
 *
 * Access to the I2C bus is closed.
 */
int opt3001_close();

#endif /* _OPT3001_H_ */

/*
 * vim: sw=4:et:ai
 */
