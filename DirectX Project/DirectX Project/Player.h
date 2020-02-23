#pragma once
#include <d3d11.h>
#include <fstream>
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
	void Render(ID3D11DeviceContext*, LightShaderClass* light_shader, LightClass* light, D3DXMATRIX view_matrix, D3DXMATRIX projection_matrix);
	void Update();
	D3DXVECTOR3& Position();
private:
	Model* model;
};


