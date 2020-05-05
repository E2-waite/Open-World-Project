 ////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"

/// Initializes the position and rotation of the camera to be at the origin of the scene.
CameraClass::CameraClass()
{
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}

XMFLOAT3& CameraClass::Rotation()
{
	return rotation;
}

XMFLOAT3 CameraClass::Position()
{
	return position;
}

void CameraClass::Render(XMVECTOR player_pos)
{
	static float phi = XM_PI / 2;
	float Cx, Cy, Cz;
	phi = rotation.y / 10;
	Cx = distance * cosf(((3.0f * XM_PI) / 2.0f) * ((rotation.x / 3) / 90)) * sinf(phi);
	Cy = distance * cosf(phi);
	Cz = distance * sinf(((3.0f * XM_PI) / 2.0f) * ((rotation.x / 3) / 90)) * sinf(phi);
	XMFLOAT3 pos;
	XMStoreFloat3(&pos, player_pos);
	position = XMFLOAT3(pos.x + Cx, pos.y + -Cy, pos.z + Cz);
	XMFLOAT3 up(0.0f, 1.0f, 0.0f);
	m_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&position), player_pos, XMLoadFloat3(&up));
}

void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}