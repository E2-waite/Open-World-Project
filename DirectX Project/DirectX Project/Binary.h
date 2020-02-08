#pragma once
#include <iostream>
#include <fstream>
#include <d3d11.h>
class Binary
{
	typedef struct BufferStruct
	{
		ID3D11Buffer* vertex_buffer;
		ID3D11Buffer* index_buffer;
	}Buffer;

public:
	Binary(std::string);
	~Binary();
	void Initialize(int);
	void Write();
	void Read();
	int NumBuffers();
	void StoreBuffer(ID3D11Buffer*, ID3D11Buffer*, int ind);
	ID3D11Buffer* GetVBuffer(int);
	ID3D11Buffer* GetIBuffer(int);
private:
	std::string file_name;
	Buffer* buffer;
	int num_models;
};