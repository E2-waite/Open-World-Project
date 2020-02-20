#pragma once

#include <iostream>  
#include <string>  
#include "Model.h"
#include "NPC.h"
#include "Lightshaderclass.h"
#include "Lightclass.h"
#include "Consts.h"
#include "Binary.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	bool Initialize(ID3D11Device*, int, int, int);
	std::ostream& SetupObjects(ID3D11Device*, int, int, std::ostream&);
	void Shutdown();
	void DeleteChunk();
	void LoadChunk(ID3D11Device*);
	void Update();
	void Render(ID3D11DeviceContext*, LightShaderClass*, LightClass*, D3DXMATRIX, D3DXMATRIX);
	bool CheckRange(D3DXVECTOR3);
	bool Loaded();
private:
	Model* floor;
	NPC* npc;
	int num_npcs = 10;
	int pos[2];
	int chunk_size = 25;
	int num_objects = 0;
	float load_range = 25;
	bool loaded = false;
	bool written = false;
	string file_name;
};