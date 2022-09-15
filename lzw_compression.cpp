#include<fstream>
#include"Code.h"
#include"avltree.h"

int lzw_compression(const char* input,const char* output) {
	std::ifstream Infile(input, std::ios_base::binary);
	obitstream Output(output);
	unsigned int length_code=9;
	AVLTree table;
	Array chain;
	Code for_adding;
	int prev_code = 0;
	char ascii[256];
	for (size_t i = 0; i < 256; ++i) {
		ascii[i] = 0;
	}
	int ch;
	unsigned long long counter_bites = 0;
	while ((ch = Infile.get()) != EOF) {
		++counter_bites;
	}
	Infile.clear();
	Infile.seekg(0, std::ios::beg);
	Output << 'l';
	Array count_bites(counter_bites);
	Output.put_out(count_bites);
	Output << '\n';
	int counter = 0;
	unsigned int bitmax =(1 << 9);
	for (size_t i = 0; i < 256; ++i) {
		Array sym((char)i);
		Code tmp(sym);
		tmp.code = i;
		table.insert(tmp);
	}
	while ((ch = Infile.get()) != EOF) {
		chain = chain + ch;
		Array str_plus_ch(chain);
		for_adding.str = str_plus_ch;
		if (table.find(for_adding) != table.end()) {
			for_adding.str = for_adding.str + (char)ch;
		}
		else {
			for_adding.code = table.size();
			table.insert(for_adding);
			if (for_adding.str.get_length() > 1) {
				Code to_file(chain.pop_back());
				to_file = table.find_elem(to_file);
				OutCode((unsigned int)to_file.code, Output, length_code);
			}
			if (table.size() >= bitmax) {
				++length_code;
				bitmax <<= 1;
			}
			Array copy_ch((char)ch);
			chain = copy_ch;
		}
	}
	if (table.size() >= bitmax) {
		++length_code;
		bitmax <<= 1;
	}
	if (chain.get_length() > 1) {
		Code to_file;
		to_file.str = chain;
		to_file = table.find_elem(to_file);
		OutCode((unsigned int)to_file.code, Output, length_code);
	}
	else {
		OutCode((unsigned int)chain[0], Output, length_code);
	}
	Output.close();
	Infile.close();
	return 0;
}

void OutCode(unsigned int code, obitstream& Output, unsigned int length_code) {
	for (size_t i = length_code; i > 0; --i) {
		Output.putBit((bool)((code >> (i-1)) & 1));
	}
}

obitstream& operator<<(Array& result, obitstream& out){
	for (size_t i = 0; i < result.get_length(); ++i) {
		out.put(result[i]);
	}
	return out;
}
