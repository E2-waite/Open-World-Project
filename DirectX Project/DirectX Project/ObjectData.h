#pragma once
#include <vector> 
#include <array>
#include <iostream>  
#include <fstream>
#include "Binary.h"
class ObjectData
{
public:
	ObjectData();
	~ObjectData();
	void Vertex(std::array<float, 3>, std::array<float, 2>, std::array<float, 3>);
	std::ostream& Serialize(std::ostream&);
	std::istream& Deserialize(std::istream&);

	std::vector<float> pos_x;
	std::vector<float> pos_y;
	std::vector<float> pos_z;
	std::vector<float> tex_x;
	std::vector<float> tex_y;
	std::vector<float> norm_x;
	std::vector<float> norm_y;
	std::vector<float> norm_z;
private:
	int num_indices = 0;
	bool vertices = false;
	unsigned long indices = 0;
	Binary* binary;
};

