#include "Binary.h"

Binary::Binary(std::string file_name) : file_name(file_name){}

Binary::~Binary(){}

int* Binary::Read()
{
	std::ifstream file;
	file.open(file_name, std::ios::in | std::ios::binary);
	static int test[10];
	file.read((char*)&test, sizeof(test));
	file.close();
	return test;
}

void Binary::Write(int var[])
{
	std::ofstream file;
	file.open(file_name, std::ios::out | std::ios::binary);
	int test[10]{10642, 18911, 288, 3, 47878, 50, 69, 72, 887, 616};
	file.write((char*)&test, sizeof(test));
	file.close();
}