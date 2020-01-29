#include "Chunk.h"

Chunk::Chunk()
{

}

Chunk::~Chunk()
{

}

bool Chunk::Initialize(ID3D11Device* device, int x, int y)
{
	pos[0] = x, pos[1] = y;
	floor = new Model;
	floor->Initialize(device, "Data/Floor.txt", "Data/Floor.dds", D3DXVECTOR3(0, 0, 0), 
		D3DXVECTOR3(pos[0] * chunk_size, -0.5, pos[1] * chunk_size), D3DXVECTOR3(chunk_size, chunk_size, chunk_size));

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
		result = npc[i].Initialize(device, "Data/Cube.txt", "Data/npc.dds", pos[0] * chunk_size, pos[1] * chunk_size, chunk_size);
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

	floor->Render(deviceContext);
	light_shader->Render(deviceContext, floor->GetIndexCount(), floor->GetWorldMatrix(), view_matrix,
		projection_matrix, floor->GetTexture(), light->GetDirection(), light->GetAmbientColour(), light->GetDiffuseColour());

	for (int i = 0; i < num_npcs; i++)
	{
		npc[i].Render(deviceContext);
		light_shader->Render(deviceContext, npc[i].GetIndexCount(), npc[i].GetWorldMatrix(), view_matrix,
			projection_matrix, npc[i].GetTexture(), light->GetDirection(), light->GetAmbientColour(), light->GetDiffuseColour());
	}
}

bool Chunk::CheckRange(D3DXVECTOR3 player_pos)
{
	D3DXVECTOR3 top_left = D3DXVECTOR3(floor->GetPosition().x, 0, floor->GetPosition().z);
	D3DXVECTOR3 top_right = D3DXVECTOR3(floor->GetPosition().x + chunk_size, 0, floor->GetPosition().z);
	D3DXVECTOR3 btm_left = D3DXVECTOR3(floor->GetPosition().x, 0, floor->GetPosition().z + chunk_size);
	D3DXVECTOR3 btm_right = D3DXVECTOR3(floor->GetPosition().x + chunk_size, 0, floor->GetPosition().z + chunk_size);
	if (sqrt(pow(player_pos.x - top_left.x, 2) + pow(player_pos.z - top_left.z, 2)) < load_range) return true;
	if (sqrt(pow(player_pos.x - top_right.x, 2) + pow(player_pos.z - top_right.z, 2)) < load_range) return true;
	if (sqrt(pow(player_pos.x - btm_left.x, 2) + pow(player_pos.z - btm_left.z, 2)) < load_range) return true;
	if (sqrt(pow(player_pos.x - btm_right.x, 2) + pow(player_pos.z - btm_right.z, 2)) < load_range) return true;
	return false;
}