/*
 * ammxf_ec_utils.cpp is part of ammxf.
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

#include <ammxf_ec_utils.hpp>

struct Mapping
{
    enum
    {
        D10 = 1, //smpte 386
        MPEG_ES = 4, //smpte rdd9
        PRORES = 0x1c, //smpte rdd44
        VC3 = 0x11, //smpte st2019-4
        J2K = 0x0c, //smpte st0422-2014
    };
};

//smpte 386
struct D10Constraints
{
    enum
    {
        IMX50_PAL = 1,
        IMX50_NTSC = 2,
        IMX40_PAL = 3,
        IMX40_NTSC = 4,
        IMX30_PAL = 5,
        IMX30_NTSC = 6,

        IMX_MIN = IMX50_PAL,
        IMX_MAX = IMX30_NTSC
    };
};


//smpte 386
struct D10Template
{
    enum
    {
        Defined = 1,
        Extended = 2
    };
};

struct StreamId
{
    enum
    {
        MPEG2 = 0x60,
    };
};

struct EssenceWrappingType
{
    enum
    {
        Frame = 1,
        Clip = 2,

        J2K_I1 = 3, //Interlaced Frame, 1 field/KLV
        J2K_I2 = 4, //Interlaced Frame, 2 fields/KLV
        J2K_F1 = 5, // Field-wrapped Picture Element
        J2K_P1 = 6, // Frame- wrappe//todo ad custom so ond Picture Element

    };
};

static const unsigned char smpte_379m_ec[] =
{
    0x06, //Object Ident
    0x0e, //label size
    0x2b, //ISO
    0x34, //SMPTE
    0x04, //Labels
    0x01, //Labels Registry
    0x01, //Labels Structure
    0xff, //Version of the Registry
    0x0d, //Organizationally Registered
    0x01, //AAF Association
    0x03, //Essence Containers
    0x01, //Version 1
    0x02, //MXF Generic Container;  if 01 - Forbidden
    0xff, //Defines the kind of mapping
    0xff, //Defined by the application specification
    0xff, //Defined by the application specification
};

static const int version_of_registry_pos = 7;

bool is_SMPTE379_ec(unsigned char * key, unsigned int count) {
    bool ec = true;
    for (unsigned int i = 0; i < count && ec; ++i)
    {
        if (i == version_of_registry_pos) {
            ec &= key[i] > 0;
            continue;
        }
        ec &= key[i] == smpte_379m_ec[i];
    }

    return ec;
}

bool is_d10_ec(unsigned char * key) {
    bool ec = is_SMPTE379_ec(key, 13);
    ec &= key[13] == Mapping::D10;
    ec &= key[14] >= D10Constraints::IMX_MIN &&
          key[14] <= D10Constraints::IMX_MAX;

    ec &= (key[15] == D10Template::Defined || D10Template::Extended);
    return ec;
}

bool is_d10_50Mbps(unsigned char * key) {
    return key[14] == D10Constraints::IMX50_NTSC || key[14] == D10Constraints::IMX50_PAL;
}

bool is_d10_40Mbps(unsigned char * key) {
    return key[14] == D10Constraints::IMX40_NTSC || key[14] == D10Constraints::IMX40_PAL;
}

bool is_d10_30Mbps(unsigned char * key) {
    return key[14] == D10Constraints::IMX30_NTSC || key[14] == D10Constraints::IMX30_PAL;
}

//SMPTE RDD9
bool is_rdd9_ec(unsigned char * key) {
    bool ec = is_SMPTE379_ec(key, 13);
    ec &= key[13] == Mapping::MPEG_ES;
    ec &= key[14] == StreamId::MPEG2;
    ec &= (key[15] == EssenceWrappingType::Frame);
    return ec;
}

//smpte rdd44
bool is_rdd44_ec(unsigned char * key) {
    bool ec = is_SMPTE379_ec(key, 13);
    //dont know why version of registry defined as 0x0d in rdd44 but we wont check it
    //ec &= key[version_of_registry_pos] == 0x0d;
    ec &= key[13] == Mapping::PRORES;
    ec &= key[14] == EssenceWrappingType::Frame;
    //16th octect unused so we dont check it
    return ec;
}

//smpte st2019-4
bool is_vc3_ec(unsigned char * key) {
    bool ec = is_SMPTE379_ec(key, 13);
    ec &= key[13] == Mapping::VC3;
    ec &= key[14] == EssenceWrappingType::Frame || key[14] == EssenceWrappingType::Clip;
    //16th octect unused so we dont check it
    return ec;
}

//smpte st0422
bool is_j2k_ec(unsigned char * key) {
    bool ec = is_SMPTE379_ec(key, 13);
    ec &= key[13] == Mapping::J2K;
    ec &= key[14] >= EssenceWrappingType::Frame && key[14] <= EssenceWrappingType::J2K_P1;
    //16th octect unused so we dont check it
    return ec;
}

