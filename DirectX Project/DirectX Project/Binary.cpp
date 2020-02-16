#include "Binary.h"

Binary::Binary(){}

Binary::~Binary(){}

std::ostream& Binary::Serialize(std::ostream& os, ID3D11Buffer* v_buffer, ID3D11Buffer* i_buffer)
{
	// Create vector for storing buffer data (Vectors can be resized to the required size, preventing 'stack-based buffer overrun')
	std::vector<BufferData> buffers;
	// Initialize buffer data class and store buffer data within it.
	BufferData data;
	data.StoreBuffers(v_buffer, i_buffer);
	// Push back buffer data into vector, then write the size of the vector to the binary file. 
	// (this allows the resizing of the vector to correct size when reading)
	buffers.push_back(data);
	auto size = buffers.size();
	os.write(reinterpret_cast<char const*>(&size), sizeof(size));
	// Then writes vector data to the binary file.
	os.write(reinterpret_cast<char const*>(buffers.data()), buffers.size() * sizeof(BufferData));
	return os;
}

std::istream& Binary::Deserialize(std::istream& is, ID3D11Buffer*& v_buffer, ID3D11Buffer*& i_buffer)
{
	// Create a vector for reading buffer data into.
	std::vector<BufferData> buffers;
	decltype(buffers.size()) size;
	// Read the required size of the vector from the binary file, then resize the vector to the correct size.
	is.read(reinterpret_cast<char*>(&size), sizeof(size));
	buffers.resize(size);
	// Read BufferData vector from the binary file, then load load buffers from BufferData class.
	is.read(reinterpret_cast<char*>(buffers.data()), buffers.size() * sizeof(BufferData));
	buffers[0].LoadBuffers(v_buffer, i_buffer);
	return is;
}