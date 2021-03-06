/*
 * ammxf_defs.hpp is part of ammxf.
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

#ifndef __AMMXF_DEFS_HPP__
#define __AMMXF_DEFS_HPP__

#include <string>

typedef unsigned char ammxf_key[16];

struct ammxf_klv_triplet
{
    ammxf_key key;
    long long position;
    long long length;
    unsigned char length_of_length;
};

struct ammxf_rational
{
    unsigned int numerator;
    unsigned int denominator;
};

#if defined(_WIN32)
typedef std::wstring ammxf_string;
#else
typedef std::string ammxf_string;
#endif

#endif //__AMMXF_DEFS_HPP__
