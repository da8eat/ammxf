/*
 * ammxf_ee_utils.cpp is part of ammxf.
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

#include <ammxf_ee_utils.hpp>

static const unsigned char smpte_379m_ee[] =
{
    0x06, //Object Ident
    0x0e, //label size
    0x2b, //ISO
    0x34, //SMPTE
    0x01, //Dictionaries
    0x02, //Essence Directory
    0x01, //Dictionary Standard
    0xff, //Version of the Registry
    0x0d, //Organizationally Registered
    0x01, //AAF Association
    0x03, //MXF Generic Container Keys
    0x01, //Version 1
    0xff, //Item Type identifier
    0xff, //Essence Element Count
    0xff, //Essence Element Type
    0xff, //Essence Element Number
};

static const int version_of_registry_pos = 7;
static const int ident_octets = 12;

struct ItemType
{
    enum
    {
        CP_Picture = 0x05, //SMPTE 326M
        CP_Sound = 0x06, //SMPTE 326M
        CP_Data = 0x07, //SMPTE 326M
        GC_Picture = 0x15,
        GC_Sound = 0x16,
        GC_Data = 0x17,
        GC_Compound = 0x18,
    };
};

bool is_SMPTE379_ee(unsigned char * key) {
    bool ec = true;
    for (int i = 0; i < ident_octets && ec; ++i)
    {
        if (i == version_of_registry_pos) {
            ec &= key[i] > 0;
            continue;
        }
        ec &= key[i] == smpte_379m_ee[i];
    }

    ec &= key[ident_octets] == ItemType::CP_Picture ||
          key[ident_octets] == ItemType::CP_Sound ||
          key[ident_octets] == ItemType::CP_Data ||
          key[ident_octets] == ItemType::GC_Picture ||
          key[ident_octets] == ItemType::GC_Sound ||
          key[ident_octets] == ItemType::GC_Sound ||
          key[ident_octets] == ItemType::GC_Compound;

    return ec;
}

bool is_SMPTE379_video_ee(unsigned char * key) {
    return key[ident_octets] == ItemType::CP_Picture || key[ident_octets] == ItemType::GC_Picture;
}

bool is_SMPTE379_audio_ee(unsigned char * key) {
    return key[ident_octets] == ItemType::CP_Sound || key[ident_octets] == ItemType::GC_Sound;
}

bool is_SMPTE379_data_ee(unsigned char * key) {
        return key[ident_octets] == ItemType::CP_Data || key[ident_octets] == ItemType::GC_Data;
}

int get_track_number(unsigned char * key) {
    return (static_cast<int>(key[ident_octets + 0]) << 24) +
           (static_cast<int>(key[ident_octets + 1]) << 16) +
           (static_cast<int>(key[ident_octets + 2]) << 8) +
           (static_cast<int>(key[ident_octets + 3]) << 0);
}

