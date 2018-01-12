/*
 * ammxf_audio_utils.hpp is part of ammxf.
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

#ifndef __AMMXF_AUDIO_UTILS_HPP__
#define __AMMXF_AUDIO_UTILS_HPP__

#include "ammxf_defs.hpp"
#include <vector>
#include <memory>

extern ammxf_rational sr_48khz;

bool is_48khz(const ammxf_rational * sample_rate);
std::vector<unsigned int> get_audio_cadence(const ammxf_rational * edit_rate, const ammxf_rational * sample_rate);

//aes3 is always 24 bit audio but we might want to read less, valid channels flagged in aes header
std::vector<unsigned char> aes3_to_pcm(unsigned char * input, unsigned int size, unsigned int bps);
std::vector<unsigned char> pcm_to_aes3(unsigned char * input, unsigned int channels, unsigned int samples, unsigned int bps);

unsigned int aes3_packet_size_to_samples(unsigned int size);

#endif //__AMMXF_AUDIO_UTILS_HPP__
