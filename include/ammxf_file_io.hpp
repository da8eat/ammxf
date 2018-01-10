/*
 * ammxf_file_io.hpp is part of ammxf.
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

#ifndef __AMMXF_FILE_IO_HPP__
#define __AMMXF_FILE_IO_HPP__

#include <memory>
#include "ammxf_defs.hpp"

struct ammxf_reader;

std::shared_ptr<ammxf_reader> create_reader(const ammxf_string & path);


#endif //__AMMXF_FILE_IO_HPP__
