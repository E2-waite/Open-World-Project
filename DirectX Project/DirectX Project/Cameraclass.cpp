 ////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"

/// Initializes the position and rotation of the camera to be at the origin of the scene.
CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 90.0f;
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

XMFLOAT3 CameraClass::GetPosition()
{
	return XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}


XMFLOAT3 CameraClass::GetRotation()
{
	return XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}

/// Uses the position and rotation of the camera to build and update the view matrix.
void CameraClass::Render(XMFLOAT3 player_pos)
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR x_up, x_position, x_lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	x_up = XMLoadFloat3(&up);
	x_position = XMLoadFloat3(&position);
	x_lookAt = XMLoadFloat3(&lookAt);
	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(roll, pitch, yaw);
	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	x_lookAt = XMVector3TransformCoord(x_lookAt, rotationMatrix);
	x_up = XMVector3TransformCoord(x_up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.

	x_lookAt = x_position + x_lookAt;
	// Finally create the view matrix from the three updated vectors.
	
	m_viewMatrix = XMMatrixLookAtLH(x_position, x_lookAt, x_up);
	return;
}

/// Provide updated view matrix to calling functions after the Render function has been called to create the view matrix.
void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}