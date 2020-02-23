#pragma once
#include <fstream>
#include <d3dx10math.h>

class TransformData
{
public:
	TransformData(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	TransformData();
	~TransformData();
	void Write(std::ostream&);
	void Read(std::istream&, D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);
private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 target_pos;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;
};

