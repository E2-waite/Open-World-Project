#pragma once
#include <fstream>
#include "Structs.h"
class BufferData
{
public:
	BufferData(int, int, VertexType*, unsigned long*);
	BufferData();
	~BufferData();
	std::ostream& Write(std::ostream&);
	std::istream& Read(std::istream&, int&, int&, VertexType*&, unsigned long*&);

private:
	int v_count = 0;
	int i_count = 0;
	VertexType* vertices;
	unsigned long* indices;
};