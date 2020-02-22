#pragma once
#include <fstream>
#include "Consts.h"
class BufferData
{
public:
	BufferData(VertexType*, unsigned long*, int, int);
	BufferData();
	~BufferData();
	std::ostream& Write(std::ostream&);
	std::istream& Read(std::istream&, VertexType*&, unsigned long*&, int&, int&);

private:
	VertexType* vertices;
	unsigned long* indices;
	int vertex_count, index_count;
};