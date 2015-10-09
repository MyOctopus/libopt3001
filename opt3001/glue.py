#
# libopt3001 - OPT3001 ambient light sensor library
#
# Copyright (C) 2015 by Artur Wroblewski <wrobell@pld-linux.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

import ctypes as ct

class Sensor(object):
    """
    OPT3001 sensor communication interface.
    """
    def __init__(self, f_dev, address):
        """
        Initialize OPT3001 ambient light sensor.

        :param f_dev: I2C device filename, i.e. /dev/i2c-0.
        :param address: I2C device address, i.e. 0x77.
        """
        self._lib = ct.CDLL('libopt3001.so.0')
        self._lib.opt3001_init(f_dev.encode(), address)
        self._p_value = ct.c_float()


    def read(self):
        """
        Read lux information from sensor.
        """
        px = self._p_value
        self._lib.opt3001_read(ct.byref(px))
        return px.value


# vim: sw=4:et:ai
