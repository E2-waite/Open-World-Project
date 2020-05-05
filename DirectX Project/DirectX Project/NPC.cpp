#include "NPC.h"

NPC::NPC()
{

}

NPC::NPC(const NPC&)
{

}

NPC::~NPC()
{

}

void NPC::LoadBuffers(ID3D11Device* device, std::istream& is) 
{ 
	model->LoadBuffers(device, is); 
}
void NPC::ShutdownBuffers() { model->ShutdownBuffers(); }
void NPC::Shutdown(std::ostream& os)
{
	// Writes NPC data when closing the game
	TransformData data(model->Position(), target_pos, model->Rotation(), model->Scale());
	data.Write(os);
}

void NPC::Create(ID3D11Device* device, const char* modelFilename, const char* textureFilename, int x, int y, std::ostream& os)
{
	// Create new NPC from scratch
	x_offset = x, y_offset = y;
	model = new Model;

	// Initialize model in random location within current chunk
	float rand_x = rand() % CHUNK_SIZE + 0;
	float rand_y = rand() % CHUNK_SIZE + 0;
	start_pos = XMFLOAT3(rand_x + x_offset, 0, rand_y + y_offset);
	model->Create(device, modelFilename, textureFilename, XMFLOAT3(0, 0, 0), start_pos, XMFLOAT3(1, 1, 1), os);

	// Find random movement target within current chunk
	rand_x = rand() % CHUNK_SIZE + 0;
	rand_y = rand() % CHUNK_SIZE + 0;
	target_pos = XMFLOAT3(rand_x + x_offset, 0, rand_y + y_offset);
	float distance = sqrt(pow(target_pos.x - start_pos.x, 2) + pow(target_pos.z - start_pos.z, 2));
	direction = XMFLOAT3((target_pos.x - start_pos.x) / distance, 0, (target_pos.z - start_pos.z) / distance);
	moving = true;
}

void NPC::Load(ID3D11Device* device, const char* textureFilename, int x, int y, std::istream& is, std::istream& npc_data)
{ 
	// Setup NPC from loaded geometry and position data from binary files
	x_offset = x, y_offset = y;
	model = new Model();

	// Read NPC position, target position, rotation and scale from binary file (written when closing previous game instance)
	XMFLOAT3 pos, rot, scl;
	TransformData data;
	data.Read(npc_data, pos, target_pos, rot, scl);
	model->Load(device, textureFilename, rot, pos, scl, is);
	start_pos = pos;

	float distance = sqrt(pow(target_pos.x - start_pos.x, 2) + pow(target_pos.z - start_pos.z, 2));
	direction = XMFLOAT3((target_pos.x - start_pos.x) / distance, 0, (target_pos.z - start_pos.z) / distance);
	moving = true;
}

void NPC::Render(ID3D11DeviceContext* deviceContext)
{
	if (!dead)
	{
		model->Render(deviceContext);
	}
}

void NPC::Frame(Grid& grid)
{
	if (!dead)
	{
		Move(grid);
		FaceDirection();
	}
}

void NPC::Move(Grid& grid)
{
	XMFLOAT3 current_dist = XMFLOAT3(model->Position().x - path_target.x, 0, model->Position().z - path_target.y);
	std::vector<Node> path;
	if (moving)
	{
		model->Position().x += (direction.x * speed * elapsed);
		model->Position().z += (direction.z * speed * elapsed);
		model->LookAt(target_pos);
		if (path.empty() && !moving)
		{
			float rand_x = rand() % CHUNK_SIZE + 0;
			float rand_y = rand() % CHUNK_SIZE + 0;
			target_pos = XMFLOAT3(rand_x + x_offset, 0, rand_y + y_offset);
			path = grid.MakePath(XMINT2((int)ceil(model->Position().x), (int)ceil(model->Position().z)), XMINT2((int)ceil(target_pos.x), (int)ceil(target_pos.z)));
			if (!path.empty())
			{
				path_target = XMFLOAT2(path[0].Pos().x, path[0].Pos().y);
				moving = true;
			}
		}
		if (current_dist.x <= 0.5f && current_dist.z <= 0.5f)
		{
			moving = false;
			if (path.empty())
			{
				return;
			}
			path_target = XMFLOAT2(path[0].Pos().x, path[0].Pos().y);

			start_pos = model->Position();
			float distance = sqrt(pow(path_target.x - start_pos.x, 2) + pow(path_target.y - start_pos.z, 2));
			direction = XMFLOAT3((path_target.x - start_pos.x) / distance, 0, (path_target.y - start_pos.z) / distance);
			moving = true;
		}
	}
}



void NPC::FaceDirection()
{
	// Sets rotation to facing direction
	float angle = atan2(direction.x, direction.z);
	float degrees = 180 * angle / XM_PI;

	bool rotating;
	bool ascend;

	if (degrees > model->Rotation().x + 5)
	{
		model->Rotation().x += 5;
	}
	else if (degrees < model->Rotation().x - 5)
	{
		model->Rotation().x -= 5;
	}
}

int NPC::GetIndexCount()
{
	return model->GetIndexCount();
}

XMMATRIX NPC::GetWorldMatrix()
{
	return model->GetWorldMatrix();
}

ID3D11ShaderResourceView* NPC::GetTexture()
{
	return model->GetTexture();
}

bool NPC::Collided(XMFLOAT3 pos)
{
	if (pos.x > model->Position().x&& pos.x < model->Position().x + model->Size().x &&
		pos.y > model->Position().y&& pos.y < model->Position().y + model->Size().y &&
		pos.z > model->Position().z&& pos.z < model->Position().z + model->Size().z)
	{
		return true;
	}
	return false;
}

void NPC::Kill()
{
	dead = true;
}