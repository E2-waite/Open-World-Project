#include "BufferData.h"

BufferData::BufferData(VertexType* vertices, unsigned long* indices, int vertex_count, int index_count)
	: vertices(vertices), indices(indices), vertex_count(vertex_count), index_count(index_count) {}

BufferData::BufferData() {}
BufferData::~BufferData() {}
void BufferData::Write(std::ostream& os)
{
	size_t size;
	size = sizeof(int);
	os.write((char*)&size, sizeof(size_t));
	os.write((char*)&vertex_count, size);

	for (int i = 0; i < vertex_count; i++)
	{
		size = sizeof(vertices[i]);
		os.write((char*)&size, sizeof(size_t));
		os.write((char*)&vertices[i], size);
	}

	size = sizeof(int);
	os.write((char*)&size, sizeof(size_t));
	os.write((char*)&index_count, size);

	for (int i = 0; i < index_count; i++)
	{
		size = sizeof(indices[i]);
		os.write((char*)&size, sizeof(size_t));
		os.write((char*)&indices[i], size);
	}
}

void BufferData::Read(std::istream& is, VertexType*& vert, unsigned long*& ind, int& v_count, int& i_count)
{
	size_t size;
	is.read((char*)&size, sizeof(size_t));
	is.read((char*)&v_count, size);

	vert = new VertexType[v_count];
	for (int i = 0; i < v_count; i++)
	{
		is.read((char*)&size, sizeof(size_t));
		is.read((char*)&vert[i], size);
	}

	is.read((char*)&size, sizeof(size_t));
	is.read((char*)&i_count, size);

	ind = new unsigned long[i_count];
	for (int i = 0; i < i_count; i++)
	{
		is.read((char*)&size, sizeof(size_t));
		is.read((char*)&ind[i], size);
	}
}