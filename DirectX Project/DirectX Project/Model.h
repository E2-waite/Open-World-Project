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
#include <fstream>
#include <array>
#include <string>
#include <sstream>
#include "Textureclass.h"
#include "Consts.h"
#include "BufferData.h"

using namespace DirectX;
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
	void Create(ID3D11Device*, const char*, const char*, XMFLOAT3 rot, XMFLOAT3 pos, XMFLOAT3 scl, std::ostream&);
	void Load(ID3D11Device*, const char*, XMFLOAT3 rot, XMFLOAT3 pos, XMFLOAT3 scl, std::istream&);
	void LoadBuffers(ID3D11Device* device, std::istream&);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	XMFLOAT3& Position();
	XMFLOAT3& Rotation();
	XMFLOAT3& Scale();
	void UpdateMatrix();
	int GetIndexCount();
	XMMATRIX GetWorldMatrix();
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
	XMMATRIX m_worldMatrix;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
	XMFLOAT3 scale;
	bool buffers_init = false;
	bool buffers_loaded = false;
};

#endif