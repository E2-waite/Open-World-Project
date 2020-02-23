////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dx10math.h>
#include <fstream>
#include <array>
#include <string>
#include <sstream>
using namespace std;
#include "Textureclass.h"
#include "Consts.h"
#include "BufferData.h"
////////////////////////////////////////////////////////////////////////////////
// Class name: Model
////////////////////////////////////////////////////////////////////////////////
class Model
{
private:
	int curr_index = 0;
public:
	Model();
	Model(const Model&);
	~Model();
	void Create(ID3D11Device*, const char*, const char*, D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXVECTOR3 scl, std::ostream&);
	void Load(ID3D11Device*, const char*, D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXVECTOR3 scl, std::istream&);
	void LoadBuffers(ID3D11Device* device, std::istream&);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	D3DXVECTOR3& Position();
	D3DXVECTOR3& Rotation();
	D3DXVECTOR3& Scale();
	void UpdateMatrix();
	int GetIndexCount();
	D3DXMATRIX GetWorldMatrix();
	ID3D11ShaderResourceView* GetTexture();
	void ShutdownBuffers();
	void DeleteVertexData();
private:
	void InitializeBuffers(ID3D11Device*, std::ostream&);
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadTexture(ID3D11Device*, const char*);
	void ReleaseTexture();
	bool LoadModel(const char*);
	void ReleaseModel();
	void SetupBuffers(ID3D11Device*, VertexType*, unsigned long*);
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ModelType* m_model;
	D3DXMATRIX m_worldMatrix;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 position;
	D3DXVECTOR3 scale;
	bool buffers_init = false;
	bool buffers_loaded = false;
};

#endif