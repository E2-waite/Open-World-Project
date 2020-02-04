////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_TextureShader = 0;
	m_Light = 0;
	m_Bitmap = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	// Create the Direct3D object
	m_D3D = new D3DClass;

	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

	if (!result)
	{
		// If D3D's initialize function fails display error message
		MessageBox(hwnd, "Could not initialize Direct3D", "Error", MB_OK);
	}

	// Setup ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(m_D3D->GetDevice(), m_D3D->GetDeviceContext());
	ImGui::StyleColorsDark();


	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(25.0f, 50.0f, 25.0f);

	binary = new Binary("chunk.bin");

	// Dynamically set up 2D chunk array
	chunk = new Chunk*[chunks_x];
	for (int i = 0; i < chunks_x; ++i)
		chunk[i] = new Chunk[chunks_y];

	for (int i = 0; i < chunks_x; ++i)
	{
		for (int j = 0; j < chunks_y; ++j)
		{
			result = chunk[i][j].Initialize(m_D3D->GetDevice(), i, j);
			if (!result)
			{
				MessageBox(hwnd, "Could not initialize chunk", "Error", MB_OK);
				return false;
			}
		}
	}
	
	player = new Player;
	result = player->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize player", "Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize the texture shader object.", "Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize the light shader object.", "Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColour(0.3f, 0.3f, 0.3f, 0.3f);
	m_Light->SetDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, -1.0f, 0.0f);

	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, "Data/crate.dds", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize the bitmap object.", "Error", MB_OK);
		return false;
	}


	return true;
}



void GraphicsClass::Shutdown()
{
	ImGui_ImplDX11_Shutdown();

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}


	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the Direct3D object.
	if (m_D3D)
	{
		// On shutdown run D3D shutdown function and delete class instance
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	return;
}


bool GraphicsClass::Update(int mouse_x, int mouse_y)
{
	bool result;
	static float rotation = 0.0f;
	// UPdate the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	for (int i = 0; i < chunks_x; ++i)
	{
		for (int j = 0; j < chunks_y; ++j)
		{
			chunk[i][j].Update();
		}
	}

	player->Update(D3DXVECTOR3(m_Camera->GetPosition().x, 0, m_Camera->GetPosition().z));

	// Call the render function each frame
	result = Render(rotation);
	if (!result)
	{
		return false;
	}
	return true;
}


bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, orthoMatrix, rotMatrix;
	D3DXVECTOR3 cam_rotation;
	bool result;
	float yaw, pitch, roll;
	cam_rotation = m_Camera->GetRotation();


	pitch = cam_rotation.x * 0.0174532925f;
	yaw = cam_rotation.y * 0.0174532925f;
	roll = cam_rotation.z * 0.0174532925f;

	D3DXMatrixRotationYawPitchRoll(&rotMatrix, yaw, pitch, roll);

	m_D3D->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	m_Camera->Render();

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Render chunks if player is in range
	for (int i = 0; i < chunks_x; ++i)
	{
		for (int j = 0; j < chunks_y; ++j)
		{
			if (chunk[i][j].CheckRange(player->Position()))
			{
				chunk[i][j].Render(m_D3D->GetDeviceContext(), m_LightShader, m_Light, viewMatrix, projectionMatrix);
			}
		}
	}

	player->Render(m_D3D->GetDeviceContext(), m_LightShader, m_Light, viewMatrix, projectionMatrix);


	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();
	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), rotMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	static float transformOffset[3] = { 0, 0, 0 };

	m_D3D->EndScene();
	return true;
}

void GraphicsClass::SetCamPos(float x, float y, float z)
{
	m_Camera->SetPosition(x, y, z);
}

void GraphicsClass::CamPosX(float x)
{
	m_Camera->SetPosition(m_Camera->GetPosition().x + x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
}

void GraphicsClass::CamPosY(float y)
{
	m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y + y, m_Camera->GetPosition().z);
}

void GraphicsClass::CamPosZ(float z)
{
	m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z + z);
}

void GraphicsClass::CamRotY(float x)
{
	m_Camera->SetRotation(m_Camera->GetRotation().x + x, m_Camera->GetRotation().y, m_Camera->GetRotation().z);
}

void GraphicsClass::CamRotX(float y)
{
	m_Camera->SetRotation(m_Camera->GetRotation().x, m_Camera->GetRotation().y + y, m_Camera->GetRotation().z);
}

void GraphicsClass::ReadTest()
{
	ofstream file;
	int* p;
	p = binary->Read();
	file.open("test.txt");
	for (int i = 0; i < 10; i++)
	{
		file << std::to_string(*(p + i)) << endl;
	}
	file.close();
}