#pragma once

#include "Model.h"
#include "NPC.h"
#include "Lightshaderclass.h"
#include "Lightclass.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	bool Initialize(ID3D11Device*, int, int);
	void Shutdown();
	void Update();
	void Render(ID3D11DeviceContext*, LightShaderClass*, LightClass*, D3DXMATRIX, D3DXMATRIX);
	bool SetupNPCs(ID3D11Device*);
	bool CheckRange(D3DXVECTOR3);
private:
	Model* floor;
	NPC* npc;
	int num_npcs = 10;
	int pos[2];
	int chunk_size = 25;
	float load_range = 25;
};