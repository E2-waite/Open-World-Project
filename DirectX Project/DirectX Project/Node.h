#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Consts.h"
using namespace DirectX;
class Node
{
public:
	Node();
	~Node();
	XMINT2& Pos();
	int& GCost();
	int& HCost();
	int FCost();
	void SetParent(Node);
	Node GetParent();
	bool HasParent();
private:
	XMINT2 position = XMINT2(0,0);
	bool has_parent = false;
	std::vector<Node> parent;
	int g_cost = 0, h_cost = 0, f_cost = 0, num_parents = 0;
};