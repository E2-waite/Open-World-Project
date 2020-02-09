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