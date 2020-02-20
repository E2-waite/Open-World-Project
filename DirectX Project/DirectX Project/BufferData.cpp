#include "BufferData.h"


BufferData::BufferData(int v_count, int i_count, VertexType* vertices, unsigned long* indices) 
					: v_count(v_count), i_count(i_count), vertices(vertices), indices(indices) {}

BufferData::BufferData() 
{
	v_count = 0;
	i_count = 0;
}
BufferData::~BufferData() {}
std::ostream& BufferData::Write(std::ostream& os)
{
	// Write vertices
	os.write((char*)&v_count, sizeof(int));
	os.write((char*)&vertices, sizeof(VertexType) * v_count);

	// Write number of indices
	os.write((char*)&i_count, sizeof(int));
	os.write((char*)&indices, sizeof(unsigned long) * i_count);
	return os;
}

std::istream& BufferData::Read(std::istream& is, int& vc, int& ic, VertexType*& vert, unsigned long*& ind)
{
	int fill1, fill2;
	is.read((char*)&fill1, sizeof(int));
	vert = new VertexType[vc];
	is.read((char*)&vert, sizeof(VertexType) * vc);

	is.read((char*)&fill2, sizeof(int));
	ind = new unsigned long[ic];
	is.read((char*)&ind, sizeof(unsigned int) * ic);
	return is;
}