#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_
#include <sstream>
#include <windows.h>
#include <DirectXMath.h>
using namespace DirectX;

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	XMFLOAT3& Rotation();
	XMFLOAT3 Position();
	float& Distance();
	void Render(XMVECTOR);
	void GetViewMatrix(XMMATRIX&);

private:
	XMFLOAT3 rotation = XMFLOAT3(0, 20, 0);
	XMFLOAT3 position = XMFLOAT3(0, 0, 0);
	XMMATRIX m_viewMatrix;
	float distance = 50;
};

#endif