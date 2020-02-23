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
#include <iostream>
#include <fstream>
#include <DirectXMath.h>
using namespace DirectX;
#include "d3dclass.h"
#include "cameraclass.h"
#include "Lightshaderclass.h"
#include "Textureshaderclass.h"
#include "Lightclass.h"
#include "bitmapclass.h"
#include "NPC.h"
#include "Chunk.h"
#include "Player.h"
#include "Consts.h"

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
	void DeleteChunks();
	void ShutdownObjects();
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Update(int,int);
	void SetCamPos(float, float, float);
	void MovePlayer(float, float);
	void CamPosY(float);
	void CamRotX(float);
	void CamRotY(float);
private:
	bool Render(float);
	bool FileExists(const std::string);
	void InitializeObjects(std::ostream&);
	void LoadObjects(std::istream&);
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	Chunk** chunk;
	Player* player;
	LightShaderClass* m_LightShader;
	TextureShaderClass* m_TextureShader;
	LightClass* m_Light;
	BitmapClass* m_Bitmap;
};
#endif