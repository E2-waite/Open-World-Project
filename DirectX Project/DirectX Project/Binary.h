#pragma once
#include <iostream>
#include <fstream>

class Binary
{
public:
	Binary(std::string);
	~Binary();
	void Write(int[]);
	int* Read();
private:
	std::string file_name;
};