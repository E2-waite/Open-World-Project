#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dx10math.h>

struct VertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
	D3DXVECTOR3 normal;
};

struct ModelType
{
	float x, y, z;
	float tu, tv;
	float nx, ny, nz;
};

const int MaxBuffers = 128;
const int chunk_size = 100;
const int chunks_x = 5, chunks_y = 5;
const std::string buffer_file = "Data/BinaryFiles/Geometry.bin";
const std::string transform_file = "Data/BinaryFiles/Transforms.bin";