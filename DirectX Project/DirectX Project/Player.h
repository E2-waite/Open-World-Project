#pragma once
#include <d3d11.h>
#include <fstream>
#include <DirectXMath.h>
using namespace DirectX;
#include "Lightshaderclass.h"
#include "Lightclass.h"
#include "Textureclass.h"
#include "Model.h"
#include "D3dclass.h"
#include "TransformData.h"
class Player
{
public:
	Player();
	~Player();
	void Initialize(ID3D11Device*, std::ostream&, XMFLOAT3);
	void Load(ID3D11Device*, std::istream&, std::istream&);
	void Shutdown(std::ostream&);
	void Render(ID3D11DeviceContext*, LightShaderClass* light_shader, LightClass* light, XMMATRIX view_matrix, XMMATRIX projection_matrix);
	void Update(XMFLOAT3 cam_pos);
	XMFLOAT3& Position();
	XMFLOAT3& Rotation();
	XMFLOAT3 Forward();
	XMFLOAT3 Left();
	float Normalize(float val, float max, float min);
private:
	Model* model;
	XMFLOAT3 forward, left;
};


