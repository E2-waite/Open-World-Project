#include "BufferData.h"


BufferData::BufferData(D3D11_BUFFER_DESC vertex_desc, D3D11_BUFFER_DESC index_desc, D3D11_SUBRESOURCE_DATA vertex_data, D3D11_SUBRESOURCE_DATA index_data)
					: vertex_desc(vertex_desc), index_desc(index_desc), vertex_data(vertex_data), index_data(index_data) {}

BufferData::BufferData() {}
BufferData::~BufferData() {}
std::ostream& BufferData::Write(std::ostream& os)
{
	size_t size;
	size = sizeof(vertex_desc);
	os.write((char*)&size, sizeof(size_t));
	os.write((char*)&vertex_desc, size);

	size = sizeof(index_desc);
	os.write((char*)&size, sizeof(size_t));
	os.write((char*)&index_desc, size);

	size = sizeof(vertex_data);
	os.write((char*)&size, sizeof(size_t));
	os.write((char*)&vertex_data, size);

	size = sizeof(index_data);
	os.write((char*)&size, sizeof(size_t));
	os.write((char*)&index_data, size);
	return os;
}

std::istream& BufferData::Read(std::istream& is, D3D11_BUFFER_DESC& v_desc, D3D11_BUFFER_DESC& i_desc, 
	D3D11_SUBRESOURCE_DATA& v_data, D3D11_SUBRESOURCE_DATA& i_data)
{
	size_t size;
	is.read((char*)&size, sizeof(size_t));
	is.read((char*)&v_desc, size);

	is.read((char*)&size, sizeof(size_t));
	is.read((char*)&i_desc, size);

	is.read((char*)&size, sizeof(size_t));
	is.read((char*)&v_data, size);

	is.read((char*)&size, sizeof(size_t));
	is.read((char*)&i_data, size);
	return is;
}