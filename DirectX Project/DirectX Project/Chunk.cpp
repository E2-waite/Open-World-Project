#include "Chunk.h"

Chunk::Chunk()
{

}

Chunk::~Chunk()
{

}

bool Chunk::Initialize(ID3D11Device* device, int x, int y, std::ostream& geometry_data)
{
	read_pos = geometry_data.tellp();
	SetupObjects(device, x, y, geometry_data);
	loaded = true;
	return true;
}

bool Chunk::Load(ID3D11Device* device, int x, int y, std::istream& geometry_data, std::istream& npc_data)
{
	read_pos = geometry_data.tellg();
	LoadObjects(device, x, y, geometry_data, npc_data);
	loaded = true;
	return true;
}


void Chunk::SetupObjects(ID3D11Device* device, int x, int y, std::ostream& geometry_data)
{
	// Setup floor:
	pos[0] = x, pos[1] = y;
	floor = new Model;
	floor->Create(device, "Data/Floor.txt", "Data/Floor.dds", XMFLOAT3(0, 0, 0),
		XMFLOAT3(pos[0] * CHUNK_SIZE, -0.5, pos[1] * CHUNK_SIZE), XMFLOAT3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE), geometry_data);
	num_objects++;

	// Setup npcs:
	srand(time(NULL));
	float x_pos = 0;
	for (int i = 0; i < NUM_NPCS; i++)
	{
		npc.push_back(new NPC());
		npc[i]->Create(device, "Data/Cube.txt", "Data/npc.dds", pos[0] * CHUNK_SIZE, pos[1] * CHUNK_SIZE, geometry_data);
		x_pos += 3;
		num_objects++;
	}
}

void Chunk::LoadObjects(ID3D11Device* device, int x, int y, std::istream& geometry_data, std::istream& npc_data)
{
	pos[0] = x, pos[1] = y;
	floor = new Model;
	floor->Load(device,  "Data/Floor.dds", XMFLOAT3(0, 0, 0),
		XMFLOAT3(pos[0] * CHUNK_SIZE, -0.5, pos[1] * CHUNK_SIZE), XMFLOAT3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE), geometry_data);
	num_objects++;

	srand(time(NULL));
	float x_pos = 0;
	for (int i = 0; i < NUM_NPCS; i++)
	{
		npc.push_back(new NPC());
		npc[i]->Load(device, "Data/npc.dds", pos[0] * CHUNK_SIZE, pos[1] * CHUNK_SIZE, geometry_data, npc_data);
		x_pos += 3;
		num_objects++;
	}
}

void Chunk::Delete()
{
	loaded = false;
	floor->ShutdownBuffers();
	for (int i = 0; i < NUM_NPCS; i++)
	{
		npc[i]->ShutdownBuffers();
	}
}

void Chunk::Shutdown(std::ostream& os)
{
	floor->Shutdown(); 
	for (int i = 0; i < NUM_NPCS; i++)
	{
		npc[i]->Shutdown(os);
	}
}

void Chunk::LoadChunk(ID3D11Device* device, std::istream& geometry_data)
{
	geometry_data.seekg(read_pos);
	floor->LoadBuffers(device, geometry_data);
	for (int i = 0; i < NUM_NPCS; i++)
	{
		npc[i]->LoadBuffers(device, geometry_data);
	}
	loaded = true;
}

void Chunk::Update(Grid& grid)
{
	if (loaded)
	{
		for (int i = 0; i < NUM_NPCS; i++)
		{
			npc[i]->Frame(grid);
		}
	}
}

void Chunk::Render(ID3D11DeviceContext* deviceContext, LightShaderClass* light_shader, LightClass* light, XMMATRIX view_matrix, XMMATRIX projection_matrix)
{
	if (loaded)
	{
		floor->Render(deviceContext);
		light_shader->Render(deviceContext, floor->GetIndexCount(), floor->GetWorldMatrix(), view_matrix,
			projection_matrix, floor->GetTexture(), light->GetDirection(), light->GetAmbientColour(), light->GetDiffuseColour());

		for (int i = 0; i < NUM_NPCS; i++)
		{
			npc[i]->Render(deviceContext);
			light_shader->Render(deviceContext, npc[i]->GetIndexCount(), npc[i]->GetWorldMatrix(), view_matrix,
				projection_matrix, npc[i]->GetTexture(), light->GetDirection(), light->GetAmbientColour(), light->GetDiffuseColour());
		}
	}
}

bool Chunk::CheckRange(XMFLOAT3 player_pos)
{
	XMFLOAT3 top_left = XMFLOAT3(floor->Position().x, 0, floor->Position().z);
	XMFLOAT3 top_right = XMFLOAT3(floor->Position().x + CHUNK_SIZE, 0, floor->Position().z);
	XMFLOAT3 btm_left = XMFLOAT3(floor->Position().x, 0, floor->Position().z + CHUNK_SIZE);
	XMFLOAT3 btm_right = XMFLOAT3(floor->Position().x + CHUNK_SIZE, 0, floor->Position().z + CHUNK_SIZE);
	if (sqrt(pow(player_pos.x - top_left.x, 2) + pow(player_pos.z - top_left.z, 2)) < CHUNK_SIZE) return true;
	if (sqrt(pow(player_pos.x - top_right.x, 2) + pow(player_pos.z - top_right.z, 2)) < CHUNK_SIZE) return true;
	if (sqrt(pow(player_pos.x - btm_left.x, 2) + pow(player_pos.z - btm_left.z, 2)) < CHUNK_SIZE) return true;
	if (sqrt(pow(player_pos.x - btm_right.x, 2) + pow(player_pos.z - btm_right.z, 2)) < CHUNK_SIZE) return true;
	return false;
}

bool Chunk::Loaded() { return loaded; }

std::vector <NPC*> Chunk::NPCs()
{
	return npc;
}

void Chunk::KillNPC(int num)
{
	npc[num]->ShutdownBuffers();
	npc.erase(npc.begin() + num);
}

int Chunk::NumNPCs()
{
	return npc.size();
}
