#pragma once
#include <vector>
#include <ctime>   
#include "NPC.h"
#include "Model.h"
class Projectile
{
public:
	Projectile();
	~Projectile();
	void Initialize(ID3D11Device*, XMFLOAT3 pos, XMFLOAT3 dir);
	void Update();
	void Delete();
	bool Expired();
	XMFLOAT3 Position();
private:
	Model* model;
	float timer = 0, lifetime = 2, speed = 2;
	XMFLOAT3 direction;
};

