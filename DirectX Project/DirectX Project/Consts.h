#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
using namespace DirectX;

struct VertexType
{
	XMFLOAT3 position;
	XMFLOAT2 texture;
	XMFLOAT3 normal;
};

struct ModelType
{
	float x, y, z;
	float tu, tv;
	float nx, ny, nz;
};
struct GridPos
{
	int x, y;
};

const int MaxBuffers = 128;
const int chunk_size = 100;
const int chunks_x = 2, chunks_y = 2;
const int node_density = 10;
const std::string buffer_file = "Data/BinaryFiles/Geometry.bin";
const std::string transform_file = "Data/BinaryFiles/Transforms.bin";