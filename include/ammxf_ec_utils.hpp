/*
 * ammxf_ec_utils.hpp is part of ammxf.
 *
 * Copyright (C) 2018 -  Alex Mogurenko <alex@mogurenko.com>
 *
 * ammxf is open source library: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ammxf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ammxf.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef __AMMXF_EC_UTILS_HPP__
#define __AMMXF_EC_UTILS_HPP__

//we will use pointer to make it compatible with other libraries like libMXF

//its possible to define how many octects should be check for compatibility
//as a rule its 13 by might be different in some particular cases
bool is_SMPTE379_ec(unsigned char * key, unsigned int count = 13);

//D10
bool is_d10_ec(unsigned char * key);

//below D10 functions doesnt check if its D10 essence container or not
//you should check it before calling any on them
bool is_d10_50Mbps(unsigned char * key);
bool is_d10_40Mbps(unsigned char * key);
bool is_d10_30Mbps(unsigned char * key);

//rdd9
bool is_rdd9_ec(unsigned char * key);

//rdd44
bool is_rdd44_ec(unsigned char * key);

//smpte st 2019-4
bool is_vc3_ec(unsigned char * key);

//smpte st0422
bool is_j2k_ec(unsigned char * key);

#endif //__AMMXF_EC_UTILS_HPP__
