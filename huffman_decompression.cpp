#include<fstream>
#include<iostream>
#include"Node.h"

void get_code(CodeTable& elem, ibitfstream& Infile) {
	unsigned int symbols_code = (unsigned int)Infile.get();
	char* code = new char[symbols_code];
	size_t i;
	for (i = 0; i < symbols_code; ++i) {
		code[i] = Infile.getBit()+'0';
	}
	Infile.getBit_to_null();
	Array copy(symbols_code, code);
	code = nullptr;
	delete[] code;
	elem.code = copy;
}

int huffman_decompression(ibitfstream& Infile, char* output) {
	int for_check = (unsigned char)Infile.get();
	if (for_check == 0)
		for_check = 256;
	unsigned int size_table = for_check;
	int ch;
	Array file_bites;
	while ((ch = Infile.get()) != '\n') {
		file_bites.push_back(ch - '0');
	}
	unsigned long long count_bites = file_bites.to_ull();
	CodeTable* table = new CodeTable[size_table];
	for (size_t j = 0; j < size_table; ++j) {
			table[j].symbol = (unsigned char)Infile.get();
			get_code(table[j], Infile);
	}
	Node* root = new Node;
	Node* main; 
	main = root;
	for (size_t i = 0; i < size_table; ++i) {
		root = main;
		for (size_t j = 0; j < table[i].code.get_length(); ++j){
			if (table[i].code[j] == '0') {
				if (root->left_descendant == nullptr) {
					root->left_descendant = new Node;
				}
				root = root->left_descendant;
			}
			else {
				if (root->right_descendant == nullptr) {
					root->right_descendant = new Node;
				}
				root = root->right_descendant;
			}
		}
		root->symbol = table[i].symbol;
		root->flag_symbol = true;
	}
	std::ofstream Out(output, std::ios_base::binary);
	root = main;
	unsigned long long counter_output_bites = 0;
	while (!Infile.eof()) {
		int ch = Infile.getBit();
		if (ch == 0)
			root = root->left_descendant;
		else {
			root = root->right_descendant;
		}
		if (root->flag_symbol && counter_output_bites < count_bites) {
				++counter_output_bites;
				Out << root->symbol;
				root = main;
		}
		else if (counter_output_bites >= count_bites) {
			break;
		}
	}
	Out.close();
	Infile.close();
	return 0;
}
