/*
 * ammxf_io.cpp is part of ammxf.
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

#include <ammxf_io.hpp>

bool read_klv_triplet(const ammxf_reader * r, ammxf_klv_triplet * klv) {
    if (!r || !klv) {
        return false;
    }

	klv -> position = r -> position();
	if (r -> read(klv -> key, sizeof(klv -> key)) != sizeof(klv -> key)) {
		return false;
	}

    return read_ber_length(r, &klv -> length, &klv -> length_of_length);
}

bool read_ber_length(const ammxf_reader * r, long long * length, unsigned char * length_of_length) {

    if (!r || !length || !length_of_length) {
        return false;
    }

    length[0] = 0;
    length_of_length[0] = 0;
    unsigned char initial_octet = 0;
    if (r -> read(&initial_octet, sizeof(initial_octet)) != sizeof(initial_octet)) {
        return false;
    }

    if (initial_octet & 0x80) {
        //long-form
        //should we handle case when initial octet == 0x80?
        //336m 3.2 allows it and says we have to determine length by alternative method

        length_of_length[0] = initial_octet & 0x7f;

        //technically there are no restrictions on length of length by 336m
        //e.g. 1111110b max possible value, 1111111b - prohibited by ISO/IEC 8825-1/8.1.3.5.c
        //but we stick on max 8 bytes long

        if (length_of_length[0] > 8) {
            false;
        }

        for (unsigned char i = 0; i < length_of_length[0]; ++i) {
            unsigned char b = 0;

            if (r -> read(&b, sizeof(b)) != sizeof(b)) {
                return false;
            }

            length[0] = length[0] << 8;
            length[0] += static_cast<long long>(b);
        }
    }
    else {
        //short-form
        length[0] = static_cast<long long>(initial_octet);
    }

    return true;
}

bool write_klv_triplet(const ammxf_writer * w, const ammxf_klv_triplet * klv){
    if (!w || !klv) {
        return false;
    }

    if (w -> write(&klv -> key[0], sizeof(klv -> key)) != sizeof(klv -> key)) {
        return false;
    }

    return write_ber_length(w, klv -> length, klv -> length_of_length);
}

//if length of length set to 0 we will automatically detect most correct length
bool write_ber_length(const ammxf_writer * w, long long length, unsigned char length_of_length) {
    //max length 8 as decided
    //basically long long is 64 bit
    unsigned char ber[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    if (length_of_length == 0) {
        if (length < 0x80) {
            unsigned char c = static_cast<unsigned char>(length);
            return w -> write(&c, sizeof(c)) == sizeof(c);
        }

        unsigned char count = 0;

        while (length) {
            ber[9 - count - 1] = static_cast<unsigned char>(length % 0xff);
            length /= 0xff;
            ++count;
        }

        ber[9 - count - 1] = 0x80 + count;
        return w -> write(&ber[9 - 1 - count], count + 1) == count + 1;
    }
    else {
        unsigned char count = 0;

        while (length) {
            ber[9 - count - 1] = static_cast<unsigned char>(length % 0xff);
            length /= 0xff;
            ++count;
        }

        if (count > length_of_length) {
            return false;
        }
        ber[9 - length_of_length - 1] = 0x80 + length_of_length;
        return w -> write(&ber[9 - 1 - length_of_length], length_of_length + 1) == length_of_length + 1;
    }
}

