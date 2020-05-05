#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Node.h"
using namespace DirectX;

class Grid
{
public:
	Grid();
	~Grid();
	void Initialize(XMINT2);
	std::vector<Node>  MakePath(XMINT2, XMINT2);
private:
	int ManhattenDistance(Node start, Node end);
	std::vector<Node> FinalPath(Node start_node, Node end_node);
	std::vector<Node> Neighbours(Node);
	Node node_grid[chunks_x * node_density][chunks_y * node_density];
	XMINT2 grid_size = XMINT2(0,0);
};

