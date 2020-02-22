#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Initialize(ID3D11Device* device, std::ostream& os)
{
	model = new Model;
	model->Create(device, "Data/Cube.txt", "Data/Player.dds", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), os);
}

void Player::Load(ID3D11Device* device, std::istream& is)
{
	model = new Model;
	model->Load(device,  "Data/Player.dds", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), is);
}

void Player::Shutdown()
{

}

void Player::Update(D3DXVECTOR3 pos)
{
	model->SetPos(pos.x, pos.y, pos.z);
}

void Player::Render(ID3D11DeviceContext* deviceContext, LightShaderClass* light_shader, LightClass* light, D3DXMATRIX view_matrix, D3DXMATRIX projection_matrix)
{
	model->Render(deviceContext);
	light_shader->Render(deviceContext, model->GetIndexCount(), model->GetWorldMatrix(), view_matrix,
		projection_matrix, model->GetTexture(), light->GetDirection(), light->GetAmbientColour(), light->GetDiffuseColour());
}

D3DXVECTOR3 Player::Position()
{
	return model->GetPosition();
}
