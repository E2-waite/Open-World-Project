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
	buffer[ind].numbers[0] = 0;
	buffer[ind].numbers[1] = 1;
	buffer[ind].numbers[2] = 2;
	buffer[ind].numbers[3] = 3;
	buffer[ind].numbers[4] = 4;
	buffer[ind].numbers[5] = 5;
	buffer[ind].numbers[6] = 6;
	buffer[ind].numbers[7] = 7;     
	buffer[ind].numbers[8] = 8;
	buffer[ind].numbers[9] = 9;
}

void Binary::Write()
{
	std::ofstream file(file_name, std::ios::binary);
	file.write((char*)&buffer, sizeof(buffer));
	file.close();
	delete[] buffer;
}

void Binary::Read()
{
	buffer = new Buffer[num_models];
	std::ifstream file(file_name, std::ios::binary);
	file.read((char*)&buffer, sizeof(buffer));
	file.close();
	std::ofstream test("test.txt");
	for (int i = 0; i < 10; i++)
	{
		test << std::to_string(buffer[0].numbers[i]) << std::endl;
	}
}

ID3D11Buffer* Binary::GetVBuffer(int ind) { return buffer[ind].vertex_buffer; }
ID3D11Buffer* Binary::GetIBuffer(int ind) { return buffer[ind].index_buffer; }