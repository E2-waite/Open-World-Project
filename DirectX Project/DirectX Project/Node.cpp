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

XMINT2& Node::Parent()
{
	return parent;
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