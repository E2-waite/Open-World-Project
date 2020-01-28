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
	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Update();
	void Render(ID3D11DeviceContext*, LightShaderClass*, LightClass*, D3DXMATRIX, D3DXMATRIX);
	bool SetupNPCs(ID3D11Device*);
private:
	Model* floor;
	NPC* npc;
	int num_npcs = 10;
};