#include "Binary.h"

Binary::Binary(std::string file_name) : file_name(file_name){}

Binary::~Binary(){}

void Binary::Initialize(int models)
{
	num_models = models;
	buffer = new Buffer[num_models];
}

void Binary::StoreBuffer(ID3D11Buffer* vb, ID3D11Buffer* ib, int ind)
{
	buffer[ind].vertex_buffer = vb;
	buffer[ind].index_buffer = ib;
}

void Binary::Write()
{
	std::ofstream file(file_name, std::ios::out | std::ios::binary);
	file.write((char*)&buffer, sizeof(buffer));
	file.close();
	//delete[] buffer;
}

void Binary::Read()
{
	//buffer = new Buffer[num_models];
	std::ifstream file(file_name, std::ios::in | std::ios::binary);
	file.read((char*)&buffer, sizeof(buffer));
	file.close();
}

ID3D11Buffer* Binary::GetVBuffer(int ind) { return buffer[ind].vertex_buffer; }
ID3D11Buffer* Binary::GetIBuffer(int ind) { return buffer[ind].index_buffer; }