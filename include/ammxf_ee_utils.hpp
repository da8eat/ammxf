/*
 * ammxf_ee_utils.hpp is part of ammxf.
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

#ifndef __AMMXF_EE_UTILS_HPP__
#define __AMMXF_EE_UTILS_HPP__

//we will use pointer to make it compatible with other libraries like libMXF
bool is_SMPTE379_ee(unsigned char * key);

//in below functions we dont check if key is really ee key
//you should call is_SMPTE379_ee before
bool is_SMPTE379_video_ee(unsigned char * key);
bool is_SMPTE379_audio_ee(unsigned char * key);
bool is_SMPTE379_data_ee(unsigned char * key);

//avid always against any rule... even when smpte 2019-4 says first 12 octets are smpte 379-1 like
//there still different key, ffmpeg also write that wierd avid key
bool is_avid_ee(unsigned char * key);

int get_track_number(unsigned char * key);

#endif //__AMMXF_EE_UTILS_HPP__
