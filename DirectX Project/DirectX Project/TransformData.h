#pragma once
#include <fstream>
#include <DirectXMath.h>
using namespace DirectX;
class TransformData
{
public:
	TransformData(XMFLOAT3, XMFLOAT3, XMFLOAT3, XMFLOAT3);
	TransformData();
	~TransformData();
	void Write(std::ostream&);
	void Read(std::istream&, XMFLOAT3&, XMFLOAT3&, XMFLOAT3&, XMFLOAT3&);
private:
	XMFLOAT3 position;
	XMFLOAT3 target_pos;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
};

