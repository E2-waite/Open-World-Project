#pragma once
#include <DirectXMath.h>
#include "Consts.h"
using namespace DirectX;
class Node
{
public:
	Node();
	~Node();
	XMINT2& Pos();
	XMINT2& Parent();
	int& GCost();
	int& HCost();
	int FCost();

private:
	XMINT2 position;
	XMINT2 parent = XMINT2(0,0);
	int g_cost = 0, h_cost = 0, f_cost = 0;
};