#pragma once
#include <fstream>
#include <string>
#include <vector>

class Binary
{
public:
	Binary();
	~Binary();
	std::ostream& Serialize(std::ostream&, std::vector<float>);

	std::istream& Deserialize(std::istream&, std::vector<float>&);
};