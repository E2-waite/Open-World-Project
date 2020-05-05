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

bool Node::Pathable()
{
	return !filled;
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
	parent = &node;
}

Node Node::GetParent()
{
	return *parent;
}