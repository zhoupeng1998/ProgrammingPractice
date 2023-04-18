#include "pch.h"

#include <iostream>

#include "mycalc.h"

int myadd(int a, int b) {
	return a + b;
}

int mysub(int a, int b) {
	return a - b;
}

int mymul(int a, int b) {
	return a * b;
}

int mydiv(int a, int b) {
	return a / b;
}

void printnum(int a) {
	std::cout << "Inside printnum: " << a << std::endl;
}