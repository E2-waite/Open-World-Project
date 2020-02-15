#pragma once

#include <math.h>
#include <time.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;
#include "Lightshaderclass.h"
#include "Lightclass.h"
#include "Textureclass.h"
#include "Model.h"
#include "D3dclass.h"
class NPC
{
public:
	NPC();
	NPC(const NPC&);
	~NPC();
	std::ostream& Initialize(ID3D11Device*, const char*, const char*, int, int, int, std::ostream&);
	void ShutdownBuffers();
	void Render(ID3D11DeviceContext*);
	void Frame();
	void Move();
	int GetIndexCount();
	D3DXMATRIX GetWorldMatrix();
	ID3D11ShaderResourceView* GetTexture();
	float GetHeight();
	unsigned long* GetIndices();
	std::array<float, 3> GetPos(int);
	std::array<float, 2> GetTex(int);
	std::array<float, 3> GetNorm(int);
private:
	Model* model;
	D3DXVECTOR3 start_pos;
	D3DXVECTOR3 target_pos;
	D3DXVECTOR3 direction;
	float distance;
	float speed = 5;
	float elapsed = 0.01f;
	bool moving = false;
	int x_offset, y_offset;
	int chunk_size;
};

