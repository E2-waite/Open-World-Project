#pragma once

#include <iostream>  
#include <string>  
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
	bool Initialize(ID3D11Device*, int, int, std::ostream&);
	bool Load(ID3D11Device*, int, int, std::istream&, std::istream&);
	void SetupObjects(ID3D11Device*, int, int, std::ostream&);
	void LoadObjects(ID3D11Device*, int, int, std::istream&, std::istream&);
	void Shutdown(std::ostream&);
	void Delete();
	void LoadChunk(ID3D11Device*, std::istream&);
	void Update();
	void Render(ID3D11DeviceContext*, LightShaderClass*, LightClass*, D3DXMATRIX, D3DXMATRIX);
	bool CheckRange(D3DXVECTOR3);
	bool Loaded();
private:
	Model* floor;
	NPC* npc;
	int num_npcs = 10;
	int pos[2];
	int num_objects = 0;
	float load_range = 25;
	bool loaded = false;
	bool written = false;
	string file_name;
	int read_pos;
};