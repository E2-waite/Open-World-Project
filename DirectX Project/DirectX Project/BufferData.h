#pragma once
#include <fstream>
#include "Consts.h"
class BufferData
{
public:
	BufferData(VertexType*, unsigned long*, int, int);
	BufferData();
	~BufferData();
	void Write(std::ostream&);
	void Read(std::istream&, VertexType*&, unsigned long*&, int&, int&);

private:
	VertexType* vertices;
	unsigned long* indices;
	int vertex_count, index_count;
};