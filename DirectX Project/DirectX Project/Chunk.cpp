#include "Chunk.h"

Chunk::Chunk()
{

}

Chunk::~Chunk()
{

}

bool Chunk::Initialize(ID3D11Device* device)
{
	bool result = true;
	result = SetupNPCs(device);
	if (!result) return false;
}

bool Chunk::SetupNPCs(ID3D11Device* device)
{
	bool result = true;
	npc = new NPC[num_npcs];
	if (!npc)
	{
		return false;
	}
	srand(time(NULL));
	float x_pos = 0;
	for (int i = 0; i < num_npcs; i++)
	{
		float rand_x = rand() % 50 + 0;
		float rand_y = rand() % 50 + 0;
		result = npc[i].Initialize(device, "Data/Cube.txt", "Data/npc.dds", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(rand_x, 0, rand_y),
			D3DXVECTOR3(0, 0, 0));
		if (!result) return false;
		x_pos += 3;
	}
}

void Chunk::Update()
{
	for (int i = 0; i < num_npcs; i++)
	{
		npc[i].Frame();
	}
}

void Chunk::Render(ID3D11DeviceContext* deviceContext, LightShaderClass* light_shader, LightClass* light, D3DXMATRIX view_matrix, D3DXMATRIX projection_matrix)
{
	for (int i = 0; i < num_npcs; i++)
	{
		npc[i].Render(deviceContext);
		light_shader->Render(deviceContext, npc[i].GetIndexCount(), npc[i].GetWorldMatrix(), view_matrix,
			projection_matrix, npc[i].GetTexture(), light->GetDirection(), light->GetAmbientColour(), light->GetDiffuseColour());
	}
}