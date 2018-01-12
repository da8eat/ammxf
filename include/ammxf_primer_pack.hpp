/*
 * ammxf_primer_pack.hpp is part of ammxf.
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

#ifndef __AMMXF_PRIMER_PACK_HPP__
#define __AMMXF_PRIMER_PACK_HPP__

#include "ammxf_defs.hpp"

struct ammxf_reader;
struct ammxf_writer;

bool is_primer_pack(unsigned char * key);

struct ammxf_primer
{
    virtual void add_record(unsigned short tag, const ammxf_key * key) = 0;
    virtual void add_dynamic_record(const ammxf_key * key) = 0;
    virtual bool has_record(const ammxf_key * key) = 0;
    virtual unsigned short get_tag(const ammxf_key * key) = 0;

    virtual bool read(const ammxf_reader * reader) = 0;
    virtual bool write(const ammxf_writer * write) = 0;
};

#endif //__AMMXF_PRIMER_PACK_HPP__
