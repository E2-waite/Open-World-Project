////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "lightclass.h"


LightClass::LightClass()
{
}


LightClass::LightClass(const LightClass& other)
{
}


LightClass::~LightClass()
{
}

void LightClass::SetAmbientColour(float red, float green, float blue, float alpha)
{
	m_ambientColour = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightClass::SetDiffuseColour(float red, float green, float blue, float alpha)
{
	m_diffuseColour = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = D3DXVECTOR3(x, y, z);
	return;
}

D3DXVECTOR4 LightClass::GetAmbientColour()
{
	return m_ambientColour;
}

D3DXVECTOR4 LightClass::GetDiffuseColour()
{
	return m_diffuseColour;
}


D3DXVECTOR3 LightClass::GetDirection()
{
	return m_direction;
}