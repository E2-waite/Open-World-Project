#pragma once
#include <fstream>
#include "Structs.h"
class BufferData
{
public:
	BufferData(D3D11_BUFFER_DESC, D3D11_BUFFER_DESC, D3D11_SUBRESOURCE_DATA, D3D11_SUBRESOURCE_DATA);
	BufferData();
	~BufferData();
	std::ostream& Write(std::ostream&);
	std::istream& Read(std::istream&, D3D11_BUFFER_DESC&, D3D11_BUFFER_DESC&, D3D11_SUBRESOURCE_DATA&, D3D11_SUBRESOURCE_DATA&);

private:
	D3D11_BUFFER_DESC vertex_desc, index_desc;
	D3D11_SUBRESOURCE_DATA vertex_data, index_data;
};