/*
 * ammxf_edit_rate.cpp is part of ammxf.
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

#include <ammxf_edit_rate.hpp>

ammxf_rational er_2398 = {
    24000,
    1001
};
ammxf_rational er_24 = {
    24,
    1
};

ammxf_rational er_25 = {
    25,
    1
};

ammxf_rational er_2997 = {
    30000,
    1001
};

ammxf_rational er_30 = {
    30,
    1
};

ammxf_rational er_48 = {
    48,
    1
};

ammxf_rational er_50 = {
    50,
    1
};

ammxf_rational er_5994 = {
    60000,
    1001
};

ammxf_rational er_60 = {
    60,
    1
};

ammxf_rational er_120 = {
    120,
    1
};

bool is_er_2398(const ammxf_rational * rate) {
    return (rate -> numerator * er_2398.denominator == er_2398.numerator * rate -> denominator);
}

bool is_er_24(const ammxf_rational * rate) {
    return (rate -> numerator * er_24.denominator == er_24.numerator * rate -> denominator);
}

bool is_er_25(const ammxf_rational * rate) {
    return (rate -> numerator * er_25.denominator == er_25.numerator * rate -> denominator);
}

bool is_er_2997(const ammxf_rational * rate) {
    return (rate -> numerator * er_2997.denominator == er_2997.numerator * rate -> denominator);
}

bool is_er_30(const ammxf_rational * rate){
    return (rate -> numerator * er_30.denominator == er_30.numerator * rate -> denominator);
}

bool is_er_48(const ammxf_rational * rate) {
    return (rate -> numerator * er_48.denominator == er_48.numerator * rate -> denominator);
}

bool is_er_50(const ammxf_rational * rate) {
    return (rate -> numerator * er_50.denominator == er_50.numerator * rate -> denominator);
}

bool is_er_5994(const ammxf_rational * rate){
    return (rate -> numerator * er_5994.denominator == er_5994.numerator * rate -> denominator);
}

bool is_er_60(const ammxf_rational * rate) {
    return (rate -> numerator * er_60.denominator == er_60.numerator * rate -> denominator);
}

bool is_er_120(const ammxf_rational * rate) {
    return (rate -> numerator * er_120.denominator == er_120.numerator * rate -> denominator);
}

