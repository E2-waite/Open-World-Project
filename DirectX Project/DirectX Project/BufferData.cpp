#include "BufferData.h"

BufferData::BufferData()
{
	v_data = 0;
	i_data = 0;
}

BufferData::~BufferData(){}

void BufferData::StoreBuffers(ID3D11Buffer* vertex_buff, ID3D11Buffer* index_buff)
{
	// Convert ID3D11Buffer to char* to allow it to be stored in class instance.
	v_data = ((char*)vertex_buff);
	i_data = ((char*)index_buff);
}

void BufferData::LoadBuffers(ID3D11Buffer*& vertex_buff, ID3D11Buffer*& index_buff)
{
	// Convert buffer data back to ID3D11Buffer type from char*
	vertex_buff = (ID3D11Buffer*)v_data;
	index_buff = (ID3D11Buffer*)i_data;
}