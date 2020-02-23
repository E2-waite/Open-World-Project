#pragma once

#include <math.h>
#include <time.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
using namespace DirectX;
using namespace std;
#include "Lightshaderclass.h"
#include "Lightclass.h"
#include "Textureclass.h"
#include "Model.h"
#include "D3dclass.h"
#include "Consts.h"
#include "TransformData.h"
class NPC
{
public:
	NPC();
	NPC(const NPC&);
	~NPC();
	void Create(ID3D11Device*, const char*, const char*, int, int,  std::ostream&);
	void Load(ID3D11Device*, const char*, int, int, std::istream&, std::istream&);
	void LoadBuffers(ID3D11Device*, std::istream&);
	void ShutdownBuffers();
	void Shutdown(std::ostream&);
	void Render(ID3D11DeviceContext*);
	void Frame();
	void Move();
	int GetIndexCount();
	XMMATRIX GetWorldMatrix();
	ID3D11ShaderResourceView* GetTexture();
private:
	Model* model;
	XMFLOAT3 start_pos;
	XMFLOAT3 target_pos;
	XMFLOAT3 direction;
	float distance;
	float speed = 5;
	float elapsed = 0.01f;
	bool moving = false;
	int x_offset, y_offset;
};

