#include "Projectile.h"


Projectile::Projectile()
{

}

Projectile::~Projectile()
{

}

void Projectile::Initialize(ID3D11Device* device, XMFLOAT3 pos, XMFLOAT3 dir)
{
	model = new Model();
	model->Create(device, "Data/Cube.txt", "Data/projectile.dds", XMFLOAT3(0,0,0), pos, XMFLOAT3(1,1,1));
	direction = dir;
}

void Projectile::Update()
{
	// Increment timer
	const clock_t begin_time = clock();
	float dt = float(clock() - begin_time) / CLOCKS_PER_SEC;
	timer += dt;
	// Update position
	model->Position() = XMFLOAT3(model->Position().x + direction.x * (speed * dt), model->Position().y + direction.y * (speed * dt), model->Position().z + direction.z * (speed * dt));
}

void Projectile::Delete()
{
	model->ShutdownBuffers();
}

bool Projectile::Expired()
{
	if (timer >= lifetime)
	{
		return true;
	}
	return false;
}

XMFLOAT3 Projectile::Position()
{
	return model->Position();
}