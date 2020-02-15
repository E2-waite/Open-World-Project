#include "Binary.h"

Binary::Binary(){}

Binary::~Binary(){}

std::ostream& Binary::SerializeBuffer(std::ostream& os, D3D11_BUFFER_DESC b_desc, D3D11_SUBRESOURCE_DATA b_data)
{
	buffer_desc.push_back(b_desc);
	buffer_data.push_back(b_data);
	SerializeDesc(os, buffer_desc);
	SerializeData(os, buffer_data);
	return os;
}

std::ostream& Binary::SerializeDesc(std::ostream& os, std::vector<D3D11_BUFFER_DESC> v)
{
	auto size = v.size();
	// Writes the size of the vector to binary
	os.write(reinterpret_cast<char const*>(&size), sizeof(size));
	// Writes the data
	os.write(reinterpret_cast<char const*>(v.data()), v.size() * sizeof(D3D11_BUFFER_DESC));
	return os;
}

std::ostream& Binary::SerializeData(std::ostream& os, std::vector<D3D11_SUBRESOURCE_DATA> v)
{
	auto size = v.size();
	// Writes the size of the vector to binary
	os.write(reinterpret_cast<char const*>(&size), sizeof(size));
	// Writes the data
	os.write(reinterpret_cast<char const*>(v.data()), v.size() * sizeof(D3D11_SUBRESOURCE_DATA));
	return os;
}

std::istream& Binary::DeserializeBuffer(std::istream& is, D3D11_BUFFER_DESC& b_desc, D3D11_SUBRESOURCE_DATA& b_data)
{
	DeserializeDesc(is, buffer_desc);
	DeserializeData(is, buffer_data);
	b_desc = buffer_desc[0];
	b_data = buffer_data[0];
	return is;
}

std::istream& Binary::DeserializeDesc(std::istream& is, std::vector<D3D11_BUFFER_DESC>& v)
{
	decltype(v.size()) size;
	// Reads the size of the upcoming data, then resizes the vector to fit the data
	is.read(reinterpret_cast<char*>(&size), sizeof(size));
	v.resize(size);
	// Reads data into vector
	is.read(reinterpret_cast<char*>(v.data()), v.size() * sizeof(D3D11_BUFFER_DESC));

	return is;
}

std::istream& Binary::DeserializeData(std::istream& is, std::vector<D3D11_SUBRESOURCE_DATA>& v)
{
	decltype(v.size()) size;
	// Reads the size of the upcoming data, then resizes the vector to fit the data
	is.read(reinterpret_cast<char*>(&size), sizeof(size));
	v.resize(size);
	// Reads data into vector
	is.read(reinterpret_cast<char*>(v.data()), v.size() * sizeof(D3D11_SUBRESOURCE_DATA));
	return is;
}