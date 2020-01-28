////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <string> 
#include <cstring>
#include <time.h>
#include "d3dclass.h"
#include "cameraclass.h"
#include "Lightshaderclass.h"
#include "Textureshaderclass.h"
#include "Lightclass.h"
#include "bitmapclass.h"
#include "NPC.h"
#include "Chunk.h"

#include "imconfig.h"
#include "IMGUI\\imgui.h"
#include "IMGUI\\imgui_impl_win32.h"
#include "IMGUI\\imgui_impl_dx11.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Update(int,int);
	void SetCamPos(float, float, float);
	void CamPosX(float);
	void CamPosY(float);
	void CamPosZ(float);
	void CamRotX(float);
	void CamRotY(float);

private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	Chunk** chunk;
	LightShaderClass* m_LightShader;
	TextureShaderClass* m_TextureShader;
	LightClass* m_Light;
	BitmapClass* m_Bitmap;
	int chunks_x = 1, chunks_y = 1;
};
#endif