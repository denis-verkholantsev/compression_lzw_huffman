#include<fstream>
#include"Node.h"

int huffman_compression(char* input, char* output) {
	std::ifstream Infile(input, std::ios_base::binary);
	unsigned long long init_table[256];
	for (size_t i = 0; i < 256; ++i) {
		init_table[i] = 0;
	}
	int ch;
	unsigned long long count_bites = 0;
	while ((ch = Infile.get()) != EOF) {
		++init_table[(unsigned char)ch];
		++count_bites;
	}
	unsigned int size_list = 0;
	for (size_t i = 0; i < 256; ++i) {
		if (init_table[i] != 0)
			++size_list;
	}
	unsigned int number_of_symbols = size_list;
	Node** list = new Node * [size_list];
	for (size_t i = 0, j = 0; i < 256; ++i) {
		if (init_table[i] != 0) {
			list[j] = new Node;
			list[j]->symbol = (unsigned char)i;
			list[j]->frequency = init_table[i];
			list[j]->flag_symbol = true;
			++j;
		}
	}
	Node** tmp;
	CodeTable* table;
	if (size_list != 1 && size_list!=0) {
		while (size_list != 1) {
			quicksort(list, 0, size_list - 1);
			Node* left_son = list[0];
			Node* right_son = list[1];
			Node* parent = new Node(left_son, right_son);
			tmp = new Node * [size_list - 1];
			tmp[0] = parent;
			for (size_t i = 1; i < size_list - 1; ++i) {
				tmp[i] = list[i + 1];
			}
			delete[] list;
			list = tmp;
			--size_list;
			tmp = nullptr;
			delete[] tmp;
		}
		Node* root = list[0];
		table = new CodeTable[number_of_symbols];
		FillingCodeTable(list[0], table);
		quicksort(table, 0, number_of_symbols - 1);
	}
	else if(size_list==1){
		table = new CodeTable[1];
		Array null('0');
		table[0].code = null;
		table[0].symbol = list[0]->symbol;
	}
	else {
		obitstream out(output);
		out.close();
		return 0;
	}
	Infile.clear();
	Infile.seekg(0, std::ios_base::beg);
	compressed_out(Infile, output, table, number_of_symbols,count_bites);
	delete[] table;
	delete[] list;
	Infile.close();
	return 0;
}

obitstream& operator<<(obitstream& out, Array& element) {
	for (size_t i = 0; i < element.get_length(); ++i) {
		out.putBit(element.get_bit_like_bool(i));
	}
	out.buffer_to_null();
	return out;
}


void compressed_out(std::ifstream& Infile, char* output, CodeTable* table, 
					unsigned int number_of_symbols, unsigned long long count_bites) {
	obitstream out(output);
	Array file_bites(count_bites);
	out << 'h' << (unsigned char)(number_of_symbols);
	size_t counter = 0;
	while (counter < file_bites.get_length()) {
		out << file_bites[counter++];
	}
	out << '\n';
	for (size_t i = 0; i < number_of_symbols; ++i) {
		out << table[i].symbol << (unsigned char)table[i].code.get_length();
		out << table[i].code;
	}
	int ch;
	while ((ch = Infile.get()) != EOF) {
		size_t num_rec = FindRecord(table, (unsigned char)ch, number_of_symbols);
		for (size_t i = 0; i < table[num_rec].code.get_length(); ++i) {
			out.putBit(table[num_rec].code.get_bit_like_bool(i));
		}
	}
	out.close();
}

size_t FindRecord(CodeTable* table, unsigned char ch, unsigned int number_of_symbols) {
	size_t i = 0;
	size_t left = 0, right = number_of_symbols;
	while (true) {
		i = (right - left) / 2 + left;
		if (ch == table[i].symbol) {
			return i;
		}
		if (ch < table[i].symbol) {
			right = i;
		}
		else {
			left = i + 1;
		}
	}
}

Array result;
unsigned int number_table = 0;
void FillingCodeTable(Node* root, CodeTable* table) {
	if (root->left_descendant != nullptr) {
		result.push_back(0);
		FillingCodeTable(root->left_descendant, table);
	}
	if (root->right_descendant != nullptr) {
		result.push_back(1);
		FillingCodeTable(root->right_descendant, table);
	}
	if (root->flag_symbol) {
		table[number_table].code = result;
		table[number_table++].symbol = root->symbol;
	}
	result.pop_back();
}

void PrintCodeTable(CodeTable* table, unsigned int number_of_symbols) {
	for (size_t i = 0; i < number_of_symbols; ++i) {
		std::cout << table[i].symbol << " - ";
		table[i].code.print();
	}
}

size_t partition(Node** nums, size_t l, size_t r) {
	Node* pivot = nums[(r - l)/2 + l];
	size_t i = l, j = r;
	while (i <= j) {
		while (nums[i]->frequency < pivot->frequency) {
			++i;
		}
		while (nums[j]->frequency > pivot->frequency) {
			--j;
		}
		if (i >= j) {
			break;
		}
		std::swap(nums[i], nums[j]);
		++i;
		--j;
	}
	return j;
}

void quicksort(Node** nums, size_t l, size_t r) {
	if (l < r) {
		size_t q = partition(nums, l, r);
		quicksort(nums, l, q);
		quicksort(nums, q + 1, r);
	}
}

size_t partition(CodeTable* nums, size_t l, size_t r) {
	unsigned char pivot = nums[(r - l)/2 + l].symbol;
	size_t i = l, j = r;
	while (i <= j) {
		while (nums[i].symbol < pivot) {
			++i;
		}
		while (nums[j].symbol > pivot) {
			--j;
		}
		if (i >= j) {
			break;
		}
		CodeTable tmp;
		tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp;
		++i;
		--j;
	}
	return j;
}

void quicksort(CodeTable* nums, size_t l, size_t r) {
	if (l < r) {
		size_t q = partition(nums, l, r);
		quicksort(nums, l, q);
		quicksort(nums, q + 1, r);
	}
}


