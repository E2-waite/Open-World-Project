#include "Chunk.h"

Chunk::Chunk()
{

}

Chunk::~Chunk()
{

}

bool Chunk::Initialize(ID3D11Device* device, int x, int y, std::ostream& os)
{
	read_pos = os.tellp();
	SetupObjects(device, x, y, os);
	loaded = true;
	return true;
}

bool Chunk::Load(ID3D11Device* device, int x, int y, std::istream& is)
{
	read_pos = is.tellg();
	LoadObjects(device, x, y, is);
	loaded = true;
	return true;
}


std::ostream& Chunk::SetupObjects(ID3D11Device* device, int x, int y, std::ostream& os)
{
	// Setup floor:
	pos[0] = x, pos[1] = y;
	floor = new Model;
	floor->Create(device, "Data/Floor.txt", "Data/Floor.dds", D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(pos[0] * chunk_size, -0.5, pos[1] * chunk_size), D3DXVECTOR3(chunk_size, chunk_size, chunk_size), os);
	num_objects++;

	// Setup npcs:
	npc = new NPC[num_npcs];
	srand(time(NULL));
	float x_pos = 0;
	for (int i = 0; i < num_npcs; i++)
	{
		npc[i].Create(device, "Data/Cube.txt", "Data/npc.dds", pos[0] * chunk_size, pos[1] * chunk_size, chunk_size, os);
		x_pos += 3;
		num_objects++;
	}
	return os;
}

void Chunk::LoadObjects(ID3D11Device* device, int x, int y, std::istream& is)
{
	pos[0] = x, pos[1] = y;
	floor = new Model;
	floor->Load(device,  "Data/Floor.dds", D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(pos[0] * chunk_size, -0.5, pos[1] * chunk_size), D3DXVECTOR3(chunk_size, chunk_size, chunk_size), is);
	num_objects++;

	npc = new NPC[num_npcs];
	srand(time(NULL));
	float x_pos = 0;
	for (int i = 0; i < num_npcs; i++)
	{
		npc[i].Load(device, "Data/npc.dds", pos[0] * chunk_size, pos[1] * chunk_size, chunk_size, is);
		x_pos += 3;
		num_objects++;
	}
}

void Chunk::DeleteChunk()
{
	loaded = false;
	floor->ShutdownBuffers();
	for (int i = 0; i < num_npcs; i++)
	{
		npc[i].ShutdownBuffers();
	}
}

void Chunk::LoadChunk(ID3D11Device* device, std::istream& is)
{
	is.seekg(read_pos);
	floor->LoadBuffers(device, is);
	for (int i = 0; i < num_npcs; i++)
	{
		npc[i].LoadBuffers(device, is);
	}
	loaded = true;
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
	if (loaded)
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

bool Chunk::Loaded() { return loaded; }