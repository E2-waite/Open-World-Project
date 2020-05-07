#pragma once

#include <math.h>
#include <time.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <math.h>
using namespace DirectX;
using namespace std;
#include "Lightshaderclass.h"
#include "Lightclass.h"
#include "Textureclass.h"
#include "Model.h"
#include "D3dclass.h"
#include "Consts.h"
#include "TransformData.h"
#include "Grid.h"
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
	void Frame(Grid&);
	void Move(Grid&);

	void FaceDirection();
	bool Collided(XMFLOAT3);
	int GetIndexCount();
	XMMATRIX GetWorldMatrix();
	ID3D11ShaderResourceView* GetTexture();
	void Kill();
	XMFLOAT3 Direction(XMFLOAT3 target);
 	float Normalize(float val, float min, float max);
	float Distance(XMFLOAT3 start, XMFLOAT3 end);
private:
	Model* model;
	XMFLOAT3 start_pos;
	XMFLOAT3 target_pos;
	XMFLOAT3 path_target;
	XMFLOAT3 direction = XMFLOAT3(0,0,0);
	float distance;
	float speed = 10;
	float elapsed = 0.01f;
	bool moving = true;
	int x_offset, y_offset;
	bool dead = false;
	std::vector<Node> path;
};

