/*
 * ammxf_io.hpp is part of ammxf.
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

#ifndef __AMMXF_IO_HPP__
#define __AMMXF_IO_HPP__

#include "ammxf_defs.hpp"

struct ammxf_reader
{
	virtual unsigned int read(void * buffer, unsigned int size) const = 0;
	virtual long long position() const = 0;
	virtual long long length() const = 0;
	virtual void seek(long long pos) const = 0;
	virtual bool eof() const = 0;
};

struct ammxf_writer
{
    virtual unsigned int write(const void * buffer, unsigned int size) const = 0;
    virtual long long position() const = 0;
    virtual void seek(long long pos) const = 0;
    virtual void seek_end() const = 0;
};

bool read_klv_triplet(const ammxf_reader * r, ammxf_klv_triplet * klv);
bool read_ber_length(const ammxf_reader * r, long long * length, unsigned char * length_of_length);

bool write_klv_triplet(const ammxf_writer * w, const ammxf_klv_triplet * klv);
//if length of length set to 0 we will automatically detect most correct length
bool write_ber_length(const ammxf_writer * w, long long length, unsigned char length_of_length);

#endif //__AMMXF_IO_HPP__
