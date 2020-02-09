#include "Serialize.h"

Serialize::Serialize()
{

}

Serialize::~Serialize()
{

}

void Serialize::Initialize(std::string f_name, int num)
{
	file_name = f_name;
	num_models = num;
}
void Serialize::Write(ID3D11Buffer* v_buffers[], ID3D11Buffer* i_buffers[])
{
	Buffer buffer[MaxBuffers];
	for (int i = 0; i < num_models; i++)
	{
		buffer[i].vertex_buffer = v_buffers[i];
		buffer[i].index_buffer = i_buffers[i];
	}
	std::ofstream file(file_name, std::ios::binary);
	file.write((char*)&buffer, sizeof(Buffer));
	file.close();
}

ID3D11Buffer* Serialize::GetVBuffer(int num)
{
	Buffer buffer[MaxBuffers];
	std::ifstream file(file_name, std::ios::binary);
	file.read((char*)&buffer[num].vertex_buffer, sizeof(buffer[num].vertex_buffer));
	ID3D11Buffer* v_buffer = buffer[num].vertex_buffer;
	return v_buffer;
}

ID3D11Buffer* Serialize::GetIBuffer(int num)
{
	Buffer buffer[MaxBuffers];
	std::ifstream file(file_name, std::ios::binary);
	file.read((char*)&buffer[num].index_buffer, sizeof(buffer[num].index_buffer));
	ID3D11Buffer* i_buffer = buffer[num].index_buffer;
	return i_buffer;
}