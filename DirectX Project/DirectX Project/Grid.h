#pragma once
#include <DirectXMath.h>
#include <vector>
#include <array>
#include "Consts.h"
#include "Node.h"
using namespace DirectX;

class Grid
{
public:
	Grid();
	~Grid();
	void Initialize(XMINT2);
	std::vector<Node> MakePath(XMINT2, XMINT2);
	bool Valid(XMINT2 pos);
private:
	int ManhattenDistance(Node start, Node end);
	int grid[CHUNKS_X * NODE_DENSITY][CHUNKS_Y * NODE_DENSITY];
	XMINT2 grid_size = XMINT2(0,0);
	const static int DIRECTIONS = 8;
	const int dx[DIRECTIONS] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	const int dy[DIRECTIONS] = { 0, 1, 1, 1, 0, -1, -1, -1 };
};

