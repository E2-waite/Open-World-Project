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

std::istream& NPC::LoadBuffers(ID3D11Device* device, std::istream& is) 
{ 
	model->LoadBuffers(device, is); 
	return is;
}
void NPC::ShutdownBuffers() { model->ShutdownBuffers(); }

std::ostream& NPC::Create(ID3D11Device* device, const char* modelFilename, const char* textureFilename, int x, int y, int size, std::ostream& os)
{
	x_offset = x, y_offset = y, chunk_size = size;
	model = new Model;

	// Initialize model in random location within current chunk
	float rand_x = rand() % chunk_size + 0;
	float rand_y = rand() % chunk_size + 0;
	start_pos = D3DXVECTOR3(rand_x + x_offset, 0, rand_y + y_offset);
	model->Create(device, modelFilename, textureFilename, D3DXVECTOR3(0, 0, 0), start_pos, D3DXVECTOR3(1, 1, 1), os);

	// Find random movement target within current chunk
	rand_x = rand() % chunk_size + 0;
	rand_y = rand() % chunk_size + 0;
	target_pos = D3DXVECTOR3(rand_x + x_offset, 0, rand_y + y_offset);
	float distance = sqrt(pow(target_pos.x - start_pos.x, 2) + pow(target_pos.z - start_pos.z, 2));
	direction = D3DXVECTOR3((target_pos.x - start_pos.x) / distance, 0, (target_pos.z - start_pos.z) / distance);
	moving = true;
	return os;
}

void NPC::Load(ID3D11Device* device, const char* textureFilename, int x, int y, int size, std::istream& is)
{
	x_offset = x, y_offset = y, chunk_size = size;
	model = new Model;

	float rand_x = rand() % chunk_size + 0;
	float rand_y = rand() % chunk_size + 0;
	start_pos = D3DXVECTOR3(rand_x + x_offset, 0, rand_y + y_offset);
	model->Load(device, textureFilename, D3DXVECTOR3(0, 0, 0), start_pos, D3DXVECTOR3(1, 1, 1), is);

	rand_x = rand() % chunk_size + 0;
	rand_y = rand() % chunk_size + 0;
	target_pos = D3DXVECTOR3(rand_x + x_offset, 0, rand_y + y_offset);
	float distance = sqrt(pow(target_pos.x - start_pos.x, 2) + pow(target_pos.z - start_pos.z, 2));
	direction = D3DXVECTOR3((target_pos.x - start_pos.x) / distance, 0, (target_pos.z - start_pos.z) / distance);
	moving = true;
}

void NPC::Render(ID3D11DeviceContext* deviceContext)
{
	model->Render(deviceContext);
}

void NPC::Frame()
{
	Move();
}

void NPC::Move()
{
	D3DXVECTOR3 current_dist = D3DXVECTOR3(model->GetPosition().x - target_pos.x, 0, model->GetPosition().z - target_pos.z);
	if (moving)
	{
		model->SetPos(model->GetPosition().x + (direction.x * speed * elapsed), 0, model->GetPosition().z + (direction.z * speed * elapsed));
		if (current_dist.x <= 0.5f && current_dist.z <= 0.5f)
		{
			moving = false;
			float rand_x = rand() % chunk_size + 0;
			float rand_y = rand() % chunk_size + 0;
			target_pos = D3DXVECTOR3(rand_x + x_offset, 0, rand_y + y_offset);
			start_pos = model->GetPosition();
			float distance = sqrt(pow(target_pos.x - start_pos.x, 2) + pow(target_pos.z - start_pos.z, 2));
			direction = D3DXVECTOR3((target_pos.x - start_pos.x) / distance, 0, (target_pos.z - start_pos.z) / distance);
			moving = true;
		}
	}
}

int NPC::GetIndexCount()
{
	return model->GetIndexCount();
}

D3DXMATRIX NPC::GetWorldMatrix()
{
	return model->GetWorldMatrix();
}

ID3D11ShaderResourceView* NPC::GetTexture()
{
	return model->GetTexture();
}

float NPC::GetHeight()
{
	return model->GetHeight();
}
