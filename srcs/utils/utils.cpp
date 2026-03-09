#include "utils.hpp"

bool	isDigit(char c) {
	return (c >= '0' && c <= '9');
}

bool	isAlNum(char c) {
	return (isDigit(c) || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}