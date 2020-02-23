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
	void Initialize(ID3D11Device*, std::ostream&);
	void Load(ID3D11Device*, std::istream&, std::istream&);
	void Shutdown(std::ostream&);
	void Render(ID3D11DeviceContext*, LightShaderClass* light_shader, LightClass* light, XMMATRIX view_matrix, XMMATRIX projection_matrix);
	void Update();
	XMFLOAT3& Position();
private:
	Model* model;
};


