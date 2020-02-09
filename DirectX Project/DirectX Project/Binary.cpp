#include "Binary.h"

Binary::Binary(){}

Binary::~Binary(){}

std::ostream& Binary::Serialize(std::ostream& os, std::vector<float> v)
{
	/*static_assert(std::is_trivial<VAR>::value && std::is_standard_layout<VAR>::value,
		"Can only serialize POD types with this function");*/

	auto size = v.size();
	// Writes the size of the vector to binary
	os.write(reinterpret_cast<char const*>(&size), sizeof(size));
	// Writes the data
	os.write(reinterpret_cast<char const*>(v.data()), v.size() * sizeof(float));
	return os;
}

std::istream& Binary::Deserialize(std::istream& is, std::vector<float>& v)
{
	/*static_assert(std::is_trivial<VAR>::value && std::is_standard_layout<VAR>::value,
		"Can only deserialize POD types with this function");*/

	decltype(v.size()) size;
	// Reads the size of the upcoming data, then resizes the vector to fit the data
	is.read(reinterpret_cast<char*>(&size), sizeof(size));
	v.resize(size);
	// Reads data into vector
	is.read(reinterpret_cast<char*>(v.data()), v.size() * sizeof(float));
	return is;
}