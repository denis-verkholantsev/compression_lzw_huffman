#pragma once
#include"array.h"
#include"bitfstreams.h"

struct Node {
	char symbol;
	unsigned long long frequency;
	bool flag_symbol;
	Node* left_descendant, *right_descendant;
	Node():frequency(0), left_descendant(nullptr), right_descendant(nullptr), flag_symbol(false) {};
	Node(Node* L, Node* R) {
		flag_symbol = false;
		left_descendant = L;
		right_descendant = R;
		frequency = L->frequency + R->frequency;
	}
	~Node() {
		if (left_descendant) 
			delete left_descendant;
		if (right_descendant) delete right_descendant;
		left_descendant = right_descendant = nullptr;
	}
	Node* operator=(const Node* X) {
		symbol = X->symbol;
		left_descendant = X->left_descendant;
		right_descendant = X->right_descendant;
		frequency = X->frequency;
		return this;
	}

};

struct CodeTable {
	unsigned char symbol;
	Array code;
	CodeTable& operator=(const CodeTable& X) {
		symbol = X.symbol;
		code = X.code;
		return*this;
	}
};

void quicksort(Node**, size_t, size_t);
size_t partition(Node**, size_t, size_t);
void quicksort(CodeTable*, size_t, size_t);
size_t partition(CodeTable*, size_t, size_t);
size_t FindRecord(CodeTable*, unsigned char, unsigned int);
void PrintCodeTable(CodeTable*, unsigned int);
int huffman_compression(char*, char*);
void FillingCodeTable(Node*, CodeTable*);
void compressed_out(std::ifstream&, char*, CodeTable*, unsigned int, unsigned long long);
obitstream& operator<<(obitstream&, Array&);

void get_code(CodeTable&, ibitfstream&);
int huffman_decompression(ibitfstream&, char*);