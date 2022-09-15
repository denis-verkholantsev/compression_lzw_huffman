#include<iostream>
#include<fstream>
#include"Node.h"
#include"avltree.h"
#include"Code.h"

bool strcmp_(const char* lhs, const char* rhs) {
	size_t i = 0, lhs_counter=0, rhs_counter=0;
	while (lhs[lhs_counter] != '\0' || rhs[rhs_counter] != '\0') {
		if (rhs[rhs_counter] != lhs[lhs_counter]) return false;
		if (lhs[lhs_counter] != '\0') ++lhs_counter;
		if (rhs[rhs_counter] != '\0') ++rhs_counter;
	}
	if (rhs_counter != lhs_counter) return false;
	return true;
}

int main(int argc,char* argv[]) {
	if (argc == 4) {
		if (strcmp_(argv[1], "-lzw")) {
			lzw_compression(argv[2], argv[3]);
		}
		else if (strcmp_(argv[1], "-huffman")) {
			huffman_compression(argv[2], argv[3]);
		}
		else if (strcmp_(argv[1], "-d")) {
			ibitfstream Infile(argv[2]);
			if (!Infile.is_open()) {
				std::cerr << "Cann not open input file";
				return -1;
			}
			char ch = Infile.get();
			if ((char)ch == 'h') {
				huffman_decompression(Infile, argv[3]);
			}
			else if ((char)ch == 'l') {
				lzw_decompression(Infile, argv[3]);
			}
			else {
				std::cerr << "Error";
				Infile.close();
				return -1;
			}
			Infile.close();
		}
	}
	else if (argc == 2 && (strcmp_(argv[1], "-h") || strcmp_(argv[1], "?"))) {
		std::cout << "For compressing:\n";
		std::cout << "1 argument - choose key of the method: -lzw or -huffman\n";
		std::cout << "2 argument - name of the input file\n";
		std::cout << "3 argument - name of the output file\n";
		std::cout << "For decompressing:'\n";
		std::cout << "1 argument - choose key -d\n";
		std::cout << "2 argument - name of the input file\n";
		std::cout << "3 argument - name of the output file\n";
	}
	return 0;
}
