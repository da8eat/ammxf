/*
 * ammxf_file_io.cpp is part of ammxf.
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

#include <ammxf_file_io.hpp>
#include <ammxf_io.hpp>

#include <cstdio>
#include <memory>
#include <cassert>

#if !defined (_WIN32)
    #include <unistd.h>
#endif

class FileReader : public ammxf_reader
{
public:
	FileReader();
	~FileReader();
public:
	bool open(const ammxf_string & path);
public:
	virtual unsigned int read(void * buffer, unsigned int size) const;
	virtual long long position() const;
	virtual long long length() const;
	virtual void seek(long long pos) const;
	virtual bool eof() const;
private:
	FILE * m_file;
	long long m_length;
};

FileReader::FileReader()
	: m_file(0)
	, m_length(0)
{
}

FileReader::~FileReader() {
	if (m_file) {
		fclose(m_file);
	}

	m_file = 0;
}

bool FileReader::open(const ammxf_string & path) {

#if defined (_WIN32)
	m_file = _wfopen(path.c_str(), L"rb");
	if (m_file) {
		_fseeki64(m_file, 0, SEEK_END);
		m_length = position();
		_fseeki64(m_file, 0, SEEK_SET);
	}
#else
	m_file = fopen(path.c_str(), "rb");

	::lseek(fileno(m_file), 0, SEEK_END);
	m_length = position();
	::lseek(fileno(m_file), 0, SEEK_SET);
	//todo
#endif

	return m_file != 0;
}
unsigned int FileReader::read(void * buffer, unsigned int size) const {

	return static_cast<unsigned int>(fread(buffer, 1, static_cast<size_t>(size), m_file));
}

long long FileReader::position() const {
	fpos_t pos = 0;
	int res = fgetpos(m_file, &pos);
	assert(res == 0);
	return pos;
}

long long FileReader::length() const {
	return m_length;
}

void FileReader::seek(long long pos) const {
	int res = fsetpos(m_file, &pos);
	assert(res == 0);
}

bool FileReader::eof() const {
	return feof(m_file) != 0;
}


std::shared_ptr<ammxf_reader> create_reader(const ammxf_string & path) {
	FileReader * reader = new (std::nothrow) FileReader();

	if (!reader || !reader -> open(path)) {
		delete reader;
                return std::shared_ptr<ammxf_reader>();
	}

        return std::shared_ptr<ammxf_reader>(reader);
}
