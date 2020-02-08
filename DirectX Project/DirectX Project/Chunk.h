#pragma once

#include <iostream>  
#include <string>  
#include "Model.h"
#include "NPC.h"
#include "Lightshaderclass.h"
#include "Lightclass.h"
#include "Binary.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	bool Initialize(ID3D11Device*, int, int, int);
	void Shutdown();
	void Update();
	void Render(ID3D11DeviceContext*, LightShaderClass*, LightClass*, D3DXMATRIX, D3DXMATRIX);
	bool SetupNPCs(ID3D11Device*);
	bool CheckRange(D3DXVECTOR3);
	void SaveBuffers();
	void LoadBuffers();
	bool Loaded();
	bool Written();
private:
	Model* floor;
	NPC* npc;
	Binary* binary;
	int num_npcs = 10;
	int pos[2];
	int chunk_size = 25;
	int num_objects = 0;
	float load_range = 25;
	bool loaded = false;
	bool written = false;
};