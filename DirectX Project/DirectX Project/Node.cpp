#include "Node.h"

Node::Node()
{

}

Node::~Node()
{

}

XMINT2& Node::Pos()
{
	return position;
}


int& Node::GCost()
{
	return g_cost;
}

int& Node::HCost()
{
	return h_cost;
}

int Node::FCost()
{
	return g_cost + h_cost;
}

void Node::SetParent(Node node)
{
	parent.push_back(node);
}

Node Node::GetParent()
{
	return parent[0];
}

bool Node::HasParent()
{
	if (parent.empty())
	{
		return false;
	}
	return true;
}