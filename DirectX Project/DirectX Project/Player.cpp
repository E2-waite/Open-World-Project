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
	model->Create(device, "Data/Cube.txt", "Data/Player.dds", XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1), os);
}

void Player::Load(ID3D11Device* device, std::istream& is, std::istream& t_data)
{
	model = new Model;
	XMFLOAT3 pos, t_pos, rot, scl;
	TransformData data;
	data.Read(t_data, pos, t_pos, rot, scl);
	model->Load(device,  "Data/Player.dds", rot, pos, scl, is);
}

void Player::Shutdown(std::ostream& os)
{
	TransformData data(model->Position(), XMFLOAT3(0,0,0), model->Rotation(), model->Scale());
	data.Write(os);
}

void Player::Update()
{
}

void Player::Render(ID3D11DeviceContext* deviceContext, LightShaderClass* light_shader, LightClass* light, XMMATRIX view_matrix, XMMATRIX projection_matrix)
{
	model->Render(deviceContext);
	light_shader->Render(deviceContext, model->GetIndexCount(), model->GetWorldMatrix(), view_matrix,
		projection_matrix, model->GetTexture(), light->GetDirection(), light->GetAmbientColour(), light->GetDiffuseColour());
}

XMFLOAT3& Player::Position()
{
	return model->Position();
}

XMFLOAT3& Player::Rotation()
{
	return model->Rotation();
}

XMFLOAT3 Player::Direction(XMFLOAT3 cam_pos)
{
	float x = model->Position().x - cam_pos.x, z = model->Position().z - cam_pos.z;
	float x_norm = Normalize(x, 0, 1), z_norm = Normalize(z, 0, 1);
	return XMFLOAT3(x_norm, 0, z_norm);
}

float Player::Normalize(float val, float min, float max)
{
	return (val - min) / (max - min);
}