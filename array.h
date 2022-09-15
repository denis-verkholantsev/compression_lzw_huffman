#pragma once
#include<iostream>
#include<fstream>
class Array {
private:
	char* result;
	unsigned int length;
public:
	Array(): length(0) {
		result = new char[0];
	};
	Array(unsigned int number_symbols, char* code) : length(number_symbols), result(code) {};
	Array(unsigned int number_symbols, const char* code) : length(number_symbols) {
		result = new char[number_symbols];
		for (size_t i = 0; i < number_symbols; ++i) {
			result[i] = code[i];
		}
	}

	Array(char X) {
		length = 1;
		result = new char[length];
		result[0] = X;
	}

	Array(const Array& X): length(X.length) {
		result = new char[length];
		for (size_t i = 0; i < length; ++i) {
			result[i] = X.result[i];
		}
	}

	Array(const char* X) {
		length = 0;
		while (X[length] != '\0') {
			++length;
		}
		result = new char[length];
		for (size_t i = 0; i < length; ++i) {
			result[i] = X[i];
		}
	}

	Array(unsigned long long count_bites) {
		if (count_bites != 0) {
			unsigned long long copy = count_bites;
			length = 0;
			while (copy) {
				copy /= 10;
				++length;
			}
			result = new char[length];
			size_t counter = 0;
			while (count_bites) {
				result[counter++] = count_bites % 10 + '0';
				count_bites /= 10;
			}
			for (size_t j = length - 1, i = 0; i < length / 2; ++i, --j) {
				std::swap(result[i], result[j]);
			}
		}
		else {
			length = 1;
			result = new char[length];
			result[0] = '0';
		}
	}
	~Array() {
		delete[] result;
		result = nullptr;
	}
	unsigned int get_length() const {
		return length;
	}
	bool get_bit_like_bool(unsigned int i) const {
		return bool(result[i]-'0');
	}
	char& operator[](unsigned int i) const {
		return result[i];
	}

	Array& operator=(const Array& X) {
		length = X.length;
		delete[] result;
		result = new char[length];
		for (size_t i = 0; i < length; ++i) {
			result[i] = X.result[i];
		}
		return *this;
	}

	Array operator+(char ch) {
		Array res;
		char* tmp = new char[length+1];
		for (size_t i = 0; i < length; ++i) {
			tmp[i] = result[i];
		}
		tmp[length] = ch;
		res.result = tmp;
		res.length = length+1;
		tmp = nullptr;
		delete[] tmp;
		return res;
	}

	bool operator<(const Array& X) {
		unsigned int min = length < X.length ? length : X.length;
		for (size_t i = 0; i < min; ++i) {
			if (result[i] < X.result[i])
				return true;
			if (result[i] > X.result[i])
				return false;
		}
		if (length < X.length)
			return true;
		if (length > X.length)
			return false;
		return false;
	}

	bool operator==(const Array & X) {
		if (length != X.length)
			return false;
		for (size_t i = 0; i < length; ++i) {
			if (result[i] != X.result[i])
				return false;
		}
		return true;
	}

	Array& push_back(unsigned int symbol) {
		char* for_adding = new char[++length];
		for (size_t i = 0; i < length-1; ++i) {
			for_adding[i] = result[i];
		}
		for_adding[length-1] = symbol + '0';
		delete[] result;
		result = for_adding;
		for_adding = nullptr;
		delete[] for_adding;
		return *this;
	}

	Array& pop_back() {
		if (length > 0) {
			--length;
			char* for_adding = new char[length];
			for (size_t i = 0; i < length; ++i) {
				for_adding[i] = result[i];
			}
			delete[] result;
			result = for_adding;
			for_adding = nullptr;
			delete[] for_adding;
		}
		return *this;
	}
	void print() {
		for (size_t i = 0; i < length; ++i) {
			std::cout << result[i];
		}
		std::cout << std::endl;
	}
	unsigned long long to_ull() {
		unsigned long long count_bites = 0;
		for (size_t i = 0; i < length; ++i) {
			count_bites += (result[i] - '0') * pow_ten(i,length);
		}
		return count_bites;
	}
	unsigned long long pow_ten(size_t i, unsigned int length) {
		unsigned long long pow_ten = 1;
		for (size_t j = 0; j < length - i - 1; ++j) {
			pow_ten *= 10;
		}
		return pow_ten;
	}
};
