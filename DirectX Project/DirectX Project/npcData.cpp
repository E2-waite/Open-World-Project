#include "npcData.h"


npcData::npcData(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale) : position(position), rotation(rotation), scale(scale){}
npcData::npcData(){}
npcData::~npcData(){}

void npcData::Write(std::ostream& os)
{
	os.write((char*)&position.x, sizeof(float));
	os.write((char*)&position.y, sizeof(float));
	os.write((char*)&position.z, sizeof(float));
	os.write((char*)&rotation.x, sizeof(float));
	os.write((char*)&rotation.y, sizeof(float));
	os.write((char*)&rotation.z, sizeof(float));
	os.write((char*)&scale.x, sizeof(float));
	os.write((char*)&scale.y, sizeof(float));
	os.write((char*)&scale.z, sizeof(float));
}

void npcData::Read(std::istream& is, D3DXVECTOR3& pos, D3DXVECTOR3& rot, D3DXVECTOR3& scl)
{
	is.read((char*)&pos.x, sizeof(float));
	is.read((char*)&pos.y, sizeof(float));
	is.read((char*)&pos.z, sizeof(float));
	is.read((char*)&rot.x, sizeof(float));
	is.read((char*)&rot.y, sizeof(float));
	is.read((char*)&rot.z, sizeof(float));
	is.read((char*)&scl.x, sizeof(float));
	is.read((char*)&scl.y, sizeof(float));
	is.read((char*)&scl.z, sizeof(float));
}
