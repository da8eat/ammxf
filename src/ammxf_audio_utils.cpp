/*
 * ammxf_audio_utils.cpp is part of ammxf.
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

#include <ammxf_audio_utils.hpp>
#include <ammxf_edit_rate.hpp>

#include <cassert>
#include <cmath>
#include <algorithm>

static const unsigned char channels_lut[16] = {
    0, 1, 1, 2, 1, 2, 2, 7, 1, 2, 2, 3, 2, 3, 3, 4
};

static const unsigned int AES3_HEADER_SIZE = 4;
static const unsigned int AES3_SAMPLE_SIZE = 4;
static const unsigned int AES3_CHANNEL_COUNT = 8;
static const unsigned int AES3_BYTES_PER_SAMPLE = 3;

ammxf_rational sr_48khz = {
    48000,
    1
};

static const std::vector<unsigned int> cadence_2398 = { 2002 };
static const std::vector<unsigned int> cadence_24 = { 2000 };
static const std::vector<unsigned int> cadence_25 = { 1920 };
static const std::vector<unsigned int> cadence_2997 = { 1602, 1601, 1602, 1601, 1602 };
static const std::vector<unsigned int> cadence_30 = { 1600 };
static const std::vector<unsigned int> cadence_48 = { 1000 };
static const std::vector<unsigned int> cadence_50 = { 960 };
static const std::vector<unsigned int> cadence_5994 = { 801, 801, 800, 801, 801 };
static const std::vector<unsigned int> cadence_60 = { 800 };
static const std::vector<unsigned int> cadence_120 = { 400 };

bool is_48khz(const ammxf_rational * sample_rate) {
    return sample_rate -> numerator * sr_48khz.denominator == sample_rate -> denominator * sr_48khz.numerator;
}

std::vector<unsigned int> get_audio_cadence(const ammxf_rational * edit_rate, const ammxf_rational * sample_rate) {

    std::vector<unsigned int> cadence;
    if (!edit_rate || !sample_rate) {
        return cadence;
    }

    if (is_48khz(sample_rate)) {
        if (is_er_2398(edit_rate)) {
            return cadence_2398;
        }
        else if (is_er_24(edit_rate)) {
            return cadence_24;
        }
        else if (is_er_25(edit_rate)) {
            return cadence_25;
        }
        else if (is_er_2997(edit_rate)) {
            return cadence_2997;
        }
        else if (is_er_30(edit_rate)) {
            return cadence_30;
        }
        else if (is_er_48(edit_rate)) {
            return cadence_48;
        }
        else if (is_er_50(edit_rate)) {
            return cadence_50;
        }
        else if (is_er_5994(edit_rate)) {
            return cadence_5994;
        }
        else if (is_er_60(edit_rate)) {
            return cadence_60;
        }
        else if (is_er_120(edit_rate)) {
            return cadence_120;
        }
    }
   
    //not sure its even possible but standard at least does not prohibit it
    cadence.push_back(sample_rate -> numerator * edit_rate -> denominator /
                      (sample_rate -> denominator * edit_rate -> numerator));
    
    return cadence;
}

std::vector<unsigned char> aes3_to_pcm(unsigned char * input, unsigned int size, unsigned int bps) {
    std::vector<unsigned char> pcm;

    //basically we check if there is enough space for header and at least 1 sample
    // and size double word aligned
    if (!input || size < 8 || size & 3) {
        return pcm;
    }

    unsigned int samples = static_cast<unsigned int>(input[1]) +
            static_cast<unsigned int>(input[2]) * 256;

    assert(samples <= 2002 && samples >= 400);//23.96 && 120
    unsigned char chans_flag = input[3];

    //4 bytes per sample * channel count * sample count + header size
    assert(AES3_SAMPLE_SIZE * AES3_CHANNEL_COUNT * samples <= size - AES3_HEADER_SIZE);
    input += AES3_HEADER_SIZE; //header size
    for (unsigned i = 0; i < samples; ++i) {
        for (unsigned int j = 0; j < AES3_CHANNEL_COUNT; ++j) {
            if (chans_flag & (1 << j)) {
                for (unsigned int k = 0; k < bps / 8; ++k) {
                    pcm.push_back(((input[1 + k + AES3_BYTES_PER_SAMPLE - bps / 8] & 0x0f) << 4) + ((input[0 + k + AES3_BYTES_PER_SAMPLE - bps / 8] & 0xf0) >> 4));
                }
            }
            input += AES3_SAMPLE_SIZE;
        }
    }

    return pcm;
}

//smpte st331m
std::vector<unsigned char> pcm_to_aes3(unsigned char * input, unsigned int channels, unsigned int samples, unsigned int bps) {
    std::vector<unsigned char> aes3;

    if (!input || !channels || !samples || !bps) {
        return aes3;
    }

    aes3.push_back(0); //FVUCP flag - 0, reserved - 0, index - 0 //todo write correct cadence index
    aes3.push_back(samples & 0xff);
    aes3.push_back((samples >> 8) & 0xff);
    aes3.push_back((1 << channels) - 1); //we just set first N flags to 1 where N == channels which means first N channels are valid

    for (unsigned int i = 0; i < samples; ++i) {
        for (unsigned int j = 0; j < channels; ++j) {
            //24 bit audio max we can put into aes3
            unsigned char smpl[3] = { 0, 0, 0 };

            for (unsigned int k = 0; k < (bps / 8) && k < 3; ++k) {
                smpl[k + 3 - std::min<unsigned int>((bps / 8), 3)] = input[k];
            }

            input += (bps / 8);

            aes3.push_back(j + (static_cast<int>(i == 0 && j == 0) << 3) + ((smpl[0] & 0x0f) << 4));
            aes3.push_back((smpl[0] >> 4) + ((smpl[1] & 0x0f) << 4));
            aes3.push_back((smpl[1] >> 4) + ((smpl[2] & 0x0f) << 4));
            aes3.push_back(smpl[2] >> 4);
        }

        for (unsigned int j = channels; j < AES3_CHANNEL_COUNT; ++j) {
            aes3.push_back(j);
            aes3.push_back(0);
            aes3.push_back(0);
            aes3.push_back(0);
        }
    }

    return aes3;
}

unsigned int aes3_packet_size_to_samples(unsigned int size) {
    if (size < AES3_HEADER_SIZE) {
        return 0;
    }

    return (size - AES3_HEADER_SIZE) / (AES3_SAMPLE_SIZE * AES3_CHANNEL_COUNT);
}

