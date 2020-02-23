////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h>
using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: LightClass
////////////////////////////////////////////////////////////////////////////////
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetAmbientColour(float, float, float, float);
	void SetDiffuseColour(float, float, float, float);
	void SetDirection(float, float, float);

	XMFLOAT4 GetAmbientColour();
	XMFLOAT4 GetDiffuseColour();
	XMFLOAT3 GetDirection();

private:
	XMFLOAT4 m_ambientColour;
	XMFLOAT4 m_diffuseColour;
	XMFLOAT3 m_direction;
};

#endif

