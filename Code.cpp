#include"Code.h"

bool less_code(const Code& Y, Code& X) {
	return Y.code < X.code;
}
bool more_code(const Code& Y, Code& X) {
	return Y.code > X.code;
}
bool eq_code(const Code& Y, Code& X) {
	return X.code == Y.code;
}