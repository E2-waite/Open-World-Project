 ////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "model.h"

/// Initializes the vertex and index buffer pointers to null
Model::Model()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_model = 0;
	position = D3DXVECTOR3(0, 0, 0);
	x_rot = 0.0; y_rot = 0.0; z_rot = 0.0;
}

Model::Model(const Model& other)
{
}

Model::~Model()
{
}
 
/// The Initialize function will call the initialization functions for the vertex and index buffers. 
std::ostream& Model::Initialize(ID3D11Device* device, const char* modelFilename, const char* textureFilename, D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXVECTOR3 scl, std::ostream& os)
{
	bool result;

	start_rot = rot;
	start_pos = pos;
	rotation = start_rot;
	position = start_pos;
	scale = scl;
	// Load in the model data.
	result = LoadModel(modelFilename);

	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	InitializeBuffers(device, os);

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);

	D3DXMatrixIdentity(&m_worldMatrix);

	return os;
}

void Model::Shutdown()
{
	//Release the model texture.
	ReleaseTexture();

	// Release the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}

/// Called from the GraphicsClass::Render function. 
/// Calls RenderBuffers to put the vertex and index buffers on the graphics pipeline so the color shader will be able to render them. 
void Model::Render(ID3D11DeviceContext* deviceContext)
{
	UpdateMatrix();
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	if (buffers_loaded)
	{
		RenderBuffers(deviceContext);
	}

	return;
}

/// Returns the number of indexes in the model
int Model::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* Model::GetTexture()
{
	return m_Texture->GetTexture();
}

/// This is where we handle creating the vertex and index buffers
/// Usually you would read in a model and create the buffers from that data file.
std::ostream& Model::InitializeBuffers(ID3D11Device* device, std::ostream& os)
{
	HRESULT result;

	// Create the vertex array.
	VertexType* vertices = new VertexType[m_vertexCount];

	// Create the index array.
	unsigned long* indices = new unsigned long[m_indexCount];


	// Load the vertex array and index array with data.
	for (int i = 0; i < m_vertexCount; i++)
	{
		if (m_model[i].y > height)
		{
			height = m_model[i].y;
		}
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
		indices[i] = i;
	}

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	/// Use vertex and index arrays to create vertex and index buffers.
	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);

	BufferData buffers(vertexBufferDesc, indexBufferDesc, vertexData, indexData);
	buffers.Write(os);

	delete[]vertices;
	delete[]indices;
	buffers_init = true;
	buffers_loaded = true;
	return os;
}

std::istream& Model::LoadBuffers(ID3D11Device* device, std::istream& is)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	BufferData buffers;
	buffers.Read(is, vertexBufferDesc, indexBufferDesc, vertexData, indexData);
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	buffers_loaded = true;
	return is;
}

void Model::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
		delete m_indexBuffer;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
		delete m_vertexBuffer;
	}
	return;
}

void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return;
}

//LoadTexture will create the texture object and then initialize it with the input file name provided. This function is called during initialization.
bool Model::LoadTexture(ID3D11Device* device, const char* filename)
{
	bool result;

	// Create the texture object.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void Model::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

bool Model::LoadModel(const char* filename)
{
	ifstream fin;
	char input;
	int i;

	// Open the model file.
	fin.open(filename);

	// Exit if could not open
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of the vertex count
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Take the vertex count from Cube.txt
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model by initializing an array for the model's vertices using the vertex count
	m_model = new ModelType[m_vertexCount];

	if (!m_model)
	{
		return false;
	}

	// Read up to beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	v_pos = new std::array<float, 3>[m_vertexCount];
	v_tex = new std::array<float, 2>[m_vertexCount];
	v_norm = new std::array<float, 3>[m_vertexCount];
	// Read in vertex data and assign to m_model
	for (int i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	fin >> num_polygons;

	fin.close();

	return true;
}

void Model::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}

bool Model::SetPos(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	return true;
}

bool Model::SetRot(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
	return true;
}

bool Model::SetScale(float x, float y, float z)
{
	scale = D3DXVECTOR3(x, y, z);
	return true;
}

D3DXVECTOR3 Model::GetPosition()
{
	return position;
}

D3DXVECTOR3 Model::GetRotation()
{
	return start_rot;
}

D3DXMATRIX Model::GetWorldMatrix()
{
	return m_worldMatrix;
}

void Model::UpdateMatrix()
{
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix, positionMatrix, scaleMatrix;

	pitch = rotation.x * 0.0174532925f;
	yaw = rotation.y * 0.0174532925f;
	roll = rotation.z * 0.0174532925f;

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	D3DXMatrixTranslation(&positionMatrix, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMatrix, scale.x, scale.y, scale.z);

	m_worldMatrix = scaleMatrix * rotationMatrix * positionMatrix;
}

int Model::GetIndCount()
{
	return m_indexCount;
}

float Model::GetHeight()
{
	return height * scale.y;
}

std::array<float, 3> Model::GetPos(int ind) { return { (float)m_model[ind].x, (float)m_model[ind].y, (float)m_model[ind].z }; }
std::array<float, 2> Model::GetTex(int ind) { return { (float)m_model[ind].tu, (float)m_model[ind].tv }; }
std::array<float, 3> Model::GetNorm(int ind) { return { (float)m_model[ind].nx, (float)m_model[ind].ny, (float)m_model[ind].nz };}
void Model::DeleteVertexData()
{
	delete[] m_model;
}