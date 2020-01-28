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
bool Model::Initialize(ID3D11Device* device, const char* modelFilename, const char* textureFilename, D3DXVECTOR3 rot, D3DXVECTOR3 pos, D3DXVECTOR3 scl)
{
	bool result;

	start_rot = rot;
	start_pos = pos;
	rotation = start_rot;
	position = start_pos;

	// Load in the model data.
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}

	D3DXMatrixIdentity(&m_worldMatrix);

	return true;
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
	RenderBuffers(deviceContext);

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
bool Model::InitializeBuffers(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

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
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

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

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	/// After vertex and index buffers have been created, delete the vertex and index arrays as they are no longer needed.
	// Release the arrays now that the vertex and index buffers have been created and loaded.

	return true;
}

/// Releases vertex and index buffers that were created in the InitializeBuffers function
void Model::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
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
	x_scl = x;
	y_scl = y;
	z_scl = z;
	return true;
}

D3DXVECTOR3 Model::GetPosition()
{
	return D3DXVECTOR3(position.x, position.y, position.z);
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
	D3DXMatrixScaling(&scaleMatrix, x_scl, y_scl, z_scl);

	m_worldMatrix = scaleMatrix * rotationMatrix * positionMatrix;
}

bool Model::WriteVector()
{
	ofstream output_file;
	output_file.open("plant.obj", std::ios_base::app);
	D3DXVECTOR4* positions;
	D3DXVECTOR3* t_coord;

	
	positions = new D3DXVECTOR4[m_vertexCount];
	t_coord = new D3DXVECTOR3[m_vertexCount];
	for (int i = 0; i < m_vertexCount; i++)
	{
		D3DXVec3Transform(&positions[i], &vertices[i].position, &m_worldMatrix);
	}

	for (int i = 0; i < m_indexCount; i++)
	{
		output_file << "v ";
		output_file << positions[indices[i]].x;
		output_file << " ";
		output_file << positions[indices[i]].y;
		output_file << " ";
		output_file << positions[indices[i]].z;
		output_file << "\n";
	}
	output_file << "\n";
	output_file.close();
	return true;
}
bool Model::WriteTex()
{
	ofstream output_file;
	output_file.open("plant.obj", std::ios_base::app);
	D3DXVECTOR4* tv_positions;
	tv_positions = new D3DXVECTOR4[m_vertexCount];
	for (int i = 0; i < m_vertexCount; i++)
	{
		//D3DXVec2TransformCoord(&tv_positions[i], &vertices[i].texture, &m_worldMatrix);
		D3DXVec2Transform(&tv_positions[i], &vertices[i].texture, &m_worldMatrix);
	}

	for (int i = 0; i < m_indexCount; i++)
	{			
		output_file << "vt ";
		output_file << vertices[indices[i]].texture.x;
		output_file << " ";
		output_file << vertices[indices[i]].texture.y;
		output_file << "\n";
	}
	return true;
}
bool Model::WriteNorm()
{
	ofstream output_file;
	output_file.open("plant.obj", std::ios_base::app);
	D3DXVECTOR3* n_positions;
	n_positions = new D3DXVECTOR3[m_vertexCount];

	for (int i = 0; i < m_vertexCount; i++)
	{
		D3DXVec3TransformNormal(&n_positions[i], &vertices[i].normal, &m_worldMatrix);
	}

	for (int i = 0; i < m_indexCount; i++)
	{		
		output_file << "vn ";
		output_file << n_positions[indices[i]].x;
		output_file << " ";
		output_file << n_positions[indices[i]].y;
		output_file << " ";
		output_file << n_positions[indices[i]].z;
		output_file << "\n";
	}
	return true;
}

int Model::WriteFaces(int offset)
{
	ofstream output_file;
	output_file.open("plant.obj", std::ios_base::app);
	int poly_ind = 1;
	for (int i = 0; i < num_polygons; i++)
	{
		output_file << "f ";
		for (int j = 0; j < 3; j++)
		{
			output_file << poly_ind + offset;
			output_file << "/";
			output_file << poly_ind + offset;
			output_file << "/";
			output_file << poly_ind + offset;
			output_file << " ";
			poly_ind++;
		}
		output_file << "\n";
	}
	return m_indexCount;
}

int Model::GetIndCount()
{
	return m_indexCount;
}

float Model::GetHeight()
{
	return height * y_scl;
}