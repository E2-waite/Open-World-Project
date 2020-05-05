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
	bool Pathable();
	Node* Clone() const { return new Node(*this); };
	int& GCost();
	int& HCost();
	int FCost();
	void SetParent(Node node);
	Node GetParent();
private:
	XMINT2 position = XMINT2(0, 0);
	bool filled = false;
	int g_cost = 0, h_cost = 0, f_cost = 0;
	Node* parent;
};