#include "TransformData.h"

TransformData::TransformData(XMFLOAT3 position, XMFLOAT3 target_pos, XMFLOAT3 rotation, XMFLOAT3 scale) : position(position), target_pos(target_pos), rotation(rotation), scale(scale) {}
TransformData::TransformData() {}
TransformData::~TransformData() {}

void TransformData::Write(std::ostream& os)
{
	os.write((char*)&position.x, sizeof(float));
	os.write((char*)&position.y, sizeof(float));
	os.write((char*)&position.z, sizeof(float));
	os.write((char*)&target_pos.x, sizeof(float));
	os.write((char*)&target_pos.y, sizeof(float));
	os.write((char*)&target_pos.z, sizeof(float));
	os.write((char*)&rotation.x, sizeof(float));
	os.write((char*)&rotation.y, sizeof(float));
	os.write((char*)&rotation.z, sizeof(float));
	os.write((char*)&scale.x, sizeof(float));
	os.write((char*)&scale.y, sizeof(float));
	os.write((char*)&scale.z, sizeof(float));
}

void TransformData::Read(std::istream& is, XMFLOAT3& pos, XMFLOAT3& t_pos, XMFLOAT3& rot, XMFLOAT3& scl)
{
	is.read((char*)&pos.x, sizeof(float));
	is.read((char*)&pos.y, sizeof(float));
	is.read((char*)&pos.z, sizeof(float));
	is.read((char*)&t_pos.x, sizeof(float));
	is.read((char*)&t_pos.y, sizeof(float));
	is.read((char*)&t_pos.z, sizeof(float));
	is.read((char*)&rot.x, sizeof(float));
	is.read((char*)&rot.y, sizeof(float));
	is.read((char*)&rot.z, sizeof(float));
	is.read((char*)&scl.x, sizeof(float));
	is.read((char*)&scl.y, sizeof(float));
	is.read((char*)&scl.z, sizeof(float));
}
