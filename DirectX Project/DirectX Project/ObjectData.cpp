#include "ObjectData.h"

ObjectData::ObjectData()
{
	binary = new Binary;
}
ObjectData::~ObjectData()
{
	delete binary;
}

void ObjectData::Vertex(std::array<float, 3> pos, std::array<float, 2> tex, std::array<float, 3> norm)
{
	pos_x.push_back(pos[0]);
	pos_y.push_back(pos[1]);
	pos_z.push_back(pos[2]);
	tex_x.push_back(tex[0]);
	tex_y.push_back(tex[1]);
	norm_x.push_back(norm[0]);
	norm_y.push_back(norm[1]);
	norm_z.push_back(norm[2]);
	vertices = true;
}

std::ostream& ObjectData::Serialize(std::ostream& os)
{
	if (vertices)
	{
		binary->Serialize(os, pos_x);
		binary->Serialize(os, pos_y);
		binary->Serialize(os, pos_z);
		binary->Serialize(os, tex_x);
		binary->Serialize(os, tex_y);
		binary->Serialize(os, norm_x);
		binary->Serialize(os, norm_y);
		binary->Serialize(os, norm_z);
	}
	return os;
}

std::istream& ObjectData::Deserialize(std::istream& is)
{
	binary->Deserialize(is, pos_x);
	binary->Deserialize(is, pos_y);
	binary->Deserialize(is, pos_z);
	binary->Deserialize(is, tex_x);
	binary->Deserialize(is, tex_y);
	binary->Deserialize(is, norm_x);
	binary->Deserialize(is, norm_y);
	binary->Deserialize(is, norm_z);
	return is;
}