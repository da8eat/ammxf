/*
 * ammxf_edit_rate.hpp is part of ammxf.
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

#ifndef __AMMXF_EDIT_RATE_HPP__
#define __AMMXF_EDIT_RATE_HPP__

#include "ammxf_defs.hpp"

extern ammxf_rational er_2398;
extern ammxf_rational er_24;
extern ammxf_rational er_25;
extern ammxf_rational er_2997;
extern ammxf_rational er_30;
extern ammxf_rational er_48;
extern ammxf_rational er_50;
extern ammxf_rational er_5994;
extern ammxf_rational er_60;
extern ammxf_rational er_120;

bool is_er_2398(const ammxf_rational * rate);
bool is_er_24(const ammxf_rational * rate);
bool is_er_25(const ammxf_rational * rate);
bool is_er_2997(const ammxf_rational * rate);
bool is_er_30(const ammxf_rational * rate);
bool is_er_48(const ammxf_rational * rate);
bool is_er_50(const ammxf_rational * rate);
bool is_er_5994(const ammxf_rational * rate);
bool is_er_60(const ammxf_rational * rate);
bool is_er_120(const ammxf_rational * rate);

#endif //__AMMXF_EDIT_RATE_HPP__
