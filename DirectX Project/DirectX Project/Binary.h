#pragma once
#include <d3d11.h>
#include <fstream>
#include <string>
#include <vector>

class Binary
{
public:
	Binary();
	~Binary();

	std::ostream& SerializeBuffer(std::ostream&, D3D11_BUFFER_DESC, D3D11_SUBRESOURCE_DATA);
	std::istream& DeserializeBuffer(std::istream&, D3D11_BUFFER_DESC&, D3D11_SUBRESOURCE_DATA&);
private:
	std::ostream& SerializeDesc(std::ostream&, std::vector<D3D11_BUFFER_DESC>);
	std::ostream& SerializeData(std::ostream&, std::vector<D3D11_SUBRESOURCE_DATA>);
	std::istream& DeserializeDesc(std::istream&, std::vector<D3D11_BUFFER_DESC>&);
	std::istream& DeserializeData(std::istream&, std::vector<D3D11_SUBRESOURCE_DATA>&);

	std::vector<D3D11_BUFFER_DESC> buffer_desc;
	std::vector<D3D11_SUBRESOURCE_DATA> buffer_data;
};