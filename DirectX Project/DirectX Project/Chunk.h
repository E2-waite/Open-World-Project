#pragma once

#include <iostream>  
#include <string>  
#include "ObjectData.h"
#include "Model.h"
#include "NPC.h"
#include "Lightshaderclass.h"
#include "Lightclass.h"
#include "Consts.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	bool Initialize(ID3D11Device*, int, int, int);
	void SetupObjects(ID3D11Device*, int, int);
	void WriteBinaryData(int);
	void ReadBinaryData(int);
	void Shutdown();
	void Update();
	void Render(ID3D11DeviceContext*, LightShaderClass*, LightClass*, D3DXMATRIX, D3DXMATRIX);
	bool CheckRange(D3DXVECTOR3);
	bool Loaded();
private:
	Model* floor;
	NPC* npc;
	ObjectData* obj_data;
	int num_npcs = 10;
	int pos[2];
	int chunk_size = 25;
	int num_objects = 0;
	float load_range = 25;
	bool loaded = false;
	bool written = false;
};