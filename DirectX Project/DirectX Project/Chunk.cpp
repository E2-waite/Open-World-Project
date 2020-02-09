#include "Chunk.h"

Chunk::Chunk()
{

}

Chunk::~Chunk()
{

}

bool Chunk::Initialize(ID3D11Device* device, int x, int y, int num)
{
	SetupObjects(device, x, y);
	WriteBinaryData(num);

	ReadBinaryData(num);
	loaded = true;
	return true;
}

void Chunk::SetupObjects(ID3D11Device* device, int x, int y)
{
	// Setup floor:
	pos[0] = x, pos[1] = y;
	floor = new Model;
	floor->Initialize(device, "Data/Floor.txt", "Data/Floor.dds", D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(pos[0] * chunk_size, -0.5, pos[1] * chunk_size), D3DXVECTOR3(chunk_size, chunk_size, chunk_size));
	num_objects++;

	// Setup npcs:
	npc = new NPC[num_npcs];
	srand(time(NULL));
	float x_pos = 0;
	for (int i = 0; i < num_npcs; i++)
	{
		npc[i].Initialize(device, "Data/Cube.txt", "Data/npc.dds", pos[0] * chunk_size, pos[1] * chunk_size, chunk_size);
		x_pos += 3;
		num_objects++;
	}
}

void Chunk::WriteBinaryData(int chunk_num)
{
	string file_name = "Data/Chunks/chunk" + to_string(chunk_num) + ".bin";
	std::ofstream bin_file(file_name, std::ofstream::trunc | std::ios::binary);
	obj_data = new ObjectData[num_objects];

	int num = 0;
	for (int i = 0; i < floor->GetIndexCount(); i++)
	{
		obj_data[num].Vertex(floor->GetPos(i), floor->GetTex(i), floor->GetNorm(i));
	}
	obj_data[num].Serialize(bin_file);
	num++;
	for (int i = 0; i < num_npcs; i++)
	{
		for (int j = 0; j < npc[i].GetIndexCount(); j++)
		{
			obj_data[num].Vertex(npc[i].GetPos(j), npc[i].GetTex(j), npc[i].GetNorm(j));
		}
		obj_data[num].Serialize(bin_file);
		num++;
	}
	bin_file.close();
	delete[] obj_data;
}

void Chunk::ReadBinaryData(int chunk_num)
{
	string file_name = "Data/Chunks/chunk" + to_string(chunk_num) + ".bin";
	std::ifstream bin_file(file_name, std::ios::binary);
	obj_data = new ObjectData[num_objects];

	int num = 0;
	obj_data[num].Deserialize(bin_file);

	num++;
	obj_data[num].Deserialize(bin_file);
	bin_file.close();

	std::ofstream myfile;
	myfile.open("LOADED_CUBE.txt");

	for (int i = 0; i < 36; i++)
	{
		myfile << std::to_string(obj_data[1].pos_x[i]) << " ";
		myfile << std::to_string(obj_data[1].pos_y[i]) << " ";
		myfile << std::to_string(obj_data[1].pos_z[i]) << std::endl;
	}
	
	myfile.close();
}

void Chunk::Shutdown()
{
	loaded = false;
	//SaveBuffers();
	//floor->ShutdownBuffers();
	//for (int i = 0; i < num_npcs; i++)
	//{
	//	npc[i].ShutdownBuffers();
	//}
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

bool Chunk::Loaded() { return loaded; }