#pragma once
#include"array.h"
#include"bitfstreams.h"

struct Code {
	Array str;
	unsigned int code;
	Code() : str(), code(0) {};
	Code(const Array& elem) : str(elem), code() {};
	Code& operator=(const Array& elem) {
		str = elem;
		code = 0;
		return *this;
	}
	bool operator<(const Code X) {
		return str < X.str;
	}
	bool operator==(const Code X) {
		return str == X.str;
	}
	bool operator>(const Code& X) {
		return !(str < X.str || str == X.str);
	}
};

int lzw_compression(const char*, const char*);
void OutCode(unsigned int code, obitstream& Output, unsigned int);

int lzw_decompression(ibitfstream&, const char*);
int getCode(ibitfstream&, unsigned int);

bool eq_code(const Code&, Code&);
bool more_code(const Code&, Code&);
bool less_code(const Code&, Code&);