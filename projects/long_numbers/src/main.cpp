#include "long_number.hpp"
#include <iostream>
#include <string>



int main() {
	std::setlocale (LC_ALL, "Russian");
	
	std::string str1;
	std::getline (std::cin, str1);
	std::string str2;
	std::getline (std::cin, str2);
	
	std::cout << std::endl;

	biv::LongNumber a1(str1.c_str());
	biv::LongNumber b2(str2.c_str());

	if (a1 == b2) {
		std::wcout << L"Равно!" << std::endl;
	} 
	if (a1 != b2) {
		std::wcout << L"Не равно!" << std::endl;
	}
	if (a1 > b2) {
		std::wcout << L"Первое больше второго!" << std::endl;
	}
	if (a1 < b2) {
		std::wcout << L"Первое меньше второго!" << std::endl;
	}
	
	std::cout << a1 << " + " << b2 << " = " << a1 + b2 << std::endl;
	std::cout << a1 << " - " << b2 << " = " << a1 - b2 << std::endl;
	std::cout << a1 << " * " << b2 << " = " << a1 * b2 << std::endl;
	std::cout << a1 << " / " << b2 << " = " << a1 / b2 << std::endl;
	std::cout << a1 << " % " << b2 << " = " << a1 % b2 << std::endl;
}