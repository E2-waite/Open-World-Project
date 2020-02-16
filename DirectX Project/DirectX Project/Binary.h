#pragma once
#include <d3d11.h>
#include <fstream>
#include <string>
#include <vector>
#include "BufferData.h"
class Binary
{
public:
	Binary();
	~Binary();
	std::ostream& Serialize(std::ostream&, ID3D11Buffer*, ID3D11Buffer*);
	std::istream& Deserialize(std::istream&, ID3D11Buffer*&, ID3D11Buffer*&);
};