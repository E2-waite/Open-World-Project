#pragma once
#include <iostream>
#include <fstream>
#include <d3d11.h>
#include <string>
#include "Chunk.h"

class Serialize
{
	struct Buffer
	{
		ID3D11Buffer* vertex_buffer;
		ID3D11Buffer* index_buffer;
	};

public:
	Serialize();
	~Serialize();
	void Initialize(std::string, int);
	void Write(ID3D11Buffer* [], ID3D11Buffer* []);
	ID3D11Buffer* GetVBuffer(int);
	ID3D11Buffer* GetIBuffer(int);
private:
	std::string file_name;
	int num_models;
};

