#pragma once
#include <fstream>
#include"array.h"

class ibitfstream : public std::ifstream {
	unsigned char buffer_;
	unsigned char bitcount_;
public:
	ibitfstream() : bitcount_(0) {}
	ibitfstream(const char* fname) :
		bitcount_(0),
		std::ifstream(fname, std::ios_base::binary) {}
	int getBit() {
		if (bitcount_ == 8) bitcount_ = 0;
		if (bitcount_ == 0) buffer_ = get();
		int i = (buffer_ & (1 << (7 - bitcount_))) ? 1 : 0;
		++bitcount_;
		return i;
	}
	bool eof() {
		if (bitcount_ > 0 && bitcount_ < 8) return false;
		if (peek() != EOF) return false;
		return true;
	}
	void getBit_to_null() {
		bitcount_ = 0;
	}
};

class obitstream : public std::ofstream {
	unsigned char buffer_;
	unsigned char bitcount_;
public:
	obitstream() : buffer_(0), bitcount_(0) {}
	obitstream(const char* fname) :
		buffer_(0), bitcount_(0),
		std::ofstream(fname, std::ios_base::binary) {}
	void putBit(bool x) {
		unsigned char S = x;
		buffer_ = buffer_ | (S << (7 - bitcount_));
		++bitcount_;
		if (bitcount_ == 8) {
			put(buffer_);
			bitcount_ = 0;
			buffer_ = 0;
		}
	}
	void close() {
		if (bitcount_ > 0)
			put(buffer_);
		bitcount_ = 0;
		buffer_ = 0;
		std::ofstream::close();
	}
	void buffer_to_null() {
		if (bitcount_) {
			put(buffer_);
		}
		buffer_ = 0;
		bitcount_ = 0;
	}
	void buffer_to_null_specifically() {
		buffer_ = 0;
		bitcount_ = 0;
	}
	obitstream& put_out(Array& result) {
		for (size_t i = 0; i < result.get_length(); ++i) {
			this->put(result[i]);
		}
		return *this;
	}
};
