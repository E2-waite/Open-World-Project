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

bool NPC::Initialize(ID3D11Device* device, const char* modelFilename, const char* textureFilename, D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXVECTOR3 scl)
{
	model = new Model;
	if (!model)
	{
		return false;
	}
	model->Initialize(device, modelFilename, textureFilename, rot, pos, scl);

	float rand_x = rand() % 50 + 0;
	float rand_y = rand() % 50 + 0;
	target_pos = D3DXVECTOR3(rand_x, 0, rand_y);
	start_pos = pos;
	float distance = sqrt(pow(target_pos.x - start_pos.x, 2) + pow(target_pos.z - start_pos.z, 2));
	direction = D3DXVECTOR3((target_pos.x - start_pos.x) / distance, 0, (target_pos.z - start_pos.z) / distance);
	moving = true;
	return true;
}

void NPC::Shutdown()
{

}

void NPC::Render(ID3D11DeviceContext* deviceContext)
{
	model->Render(deviceContext);
}

void NPC::Frame()
{
	D3DXVECTOR3 current_dist = D3DXVECTOR3(model->GetPosition().x - target_pos.x, 0, model->GetPosition().z - target_pos.z);
	if (moving)
	{
		model->SetPos(model->GetPosition().x + (direction.x * speed * elapsed), 0, model->GetPosition().z + (direction.z * speed * elapsed));
		if (current_dist.x <= 0.5f && current_dist.z <= 0.5f)
		{
			moving = false;
			float rand_x = rand() % 50 + 0;
			float rand_y = rand() % 50 + 0;
			target_pos = D3DXVECTOR3(rand_x, 0, rand_y);
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