#include<fstream>
#include"Code.h"
#include"avltree.h"

int lzw_decompression(ibitfstream& Infile, const char* output) {
	std::ofstream Output(output, std::ios_base::binary);
	AVLTree table;
	unsigned long long count_bites_abs = 0,count_bites_processing=0;
	int ch;
	Array count_bites;
	while ((ch = Infile.get()) != '\n') {
		count_bites.push_back(ch-'0');
	}
	count_bites_abs = count_bites.to_ull();
	unsigned int length_code = 9;
	int bitmax = (1 << 9);
	Code str_ch;
	for (size_t i = 0; i < 256; ++i) {
		Array sym((char)i);
		Code tmp(sym);
		tmp.code = i;
		table.insert_by_code(tmp);
	}
	ch = getCode(Infile, length_code);
	Output << (char)ch;
	++count_bites_processing;
	Code old;
	old.code = ch;
	old.str = (char)ch;
	while (count_bites_processing < count_bites_abs) {
		if (table.size() >= bitmax-1) {
			++length_code;
			bitmax <<= 1;
		}
		ch = getCode(Infile,length_code);
		str_ch.code = (unsigned int)ch;
		if (table.find_by_code(str_ch) != table.end()) {
			str_ch = table.find_by_code_elem(str_ch);
			for (size_t i = 0; i < str_ch.str.get_length(); ++i) {
				Output << str_ch.str[i];
				++count_bites_processing;
			}
			str_ch.str = old.str + str_ch.str[0];
			str_ch.code = table.size();
			table.insert_by_code(str_ch);
			old.code = ch;
			old = table.find_by_code_elem(old);
		}
		else {
				str_ch.str = old.str + old.str[0];
				str_ch.code = table.size();
				for (size_t i = 0; i < str_ch.str.get_length(); ++i) {
					Output << str_ch.str[i];
					++count_bites_processing;
				}
				table.insert_by_code(str_ch);
				old.code = ch;
				old = table.find_by_code_elem(old);
		}
	}
	Output.close();
	return 0;
}

int getCode(ibitfstream& Infile, unsigned int length_code) {
	int ch=0;
	for (size_t i = 0; i < length_code-1; ++i) {
		ch |= Infile.getBit();
		ch <<= 1;
	}
	ch |= Infile.getBit();
	return ch;
}
