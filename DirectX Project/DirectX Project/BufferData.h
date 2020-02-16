#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <d3d11.h>
#include <algorithm>
#include <vector>
class BufferData
{
public:
	BufferData();
	~BufferData();
	virtual void StoreBuffers(ID3D11Buffer*, ID3D11Buffer*);
	virtual void LoadBuffers(ID3D11Buffer*&, ID3D11Buffer*&);
private:
	char* v_data;
	char* i_data;
};

