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

const int MAX_BUFFERS = 128;
const int CHUNK_SIZE = 100;
const int CHUNKS_X = 4, CHUNKS_Y = 4;
const int NUM_NPCS = 2;
const int NODE_DENSITY = 10;
const float MAX_ANGLE = 30, MIN_ANGLE = 20;
const std::string BUFFER_FILE = "Data/BinaryFiles/Geometry.bin";
const std::string TRANSFORMATION_FILE = "Data/BinaryFiles/Transforms.bin";