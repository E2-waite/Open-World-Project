#include "Grid.h"


Grid::Grid()
{

}

Grid::~Grid()
{

}

void Grid::Initialize(XMINT2 size)
{
	grid_size = size;
	//// Sets up node grid for AI pathfinding

	for (int x = 0; x < grid_size.x; x++)
	{
		for (int y = 0; y < grid_size.y; y++)
		{
			node_grid[x][y].Pos() = XMINT2((chunk_size * x) / node_density, (chunk_size * y) / node_density);
		}
	}

}


std::vector<Node> Grid::MakePath(XMINT2 from_pos, XMINT2 to_pos)
{
	Node end_node = node_grid[(int)ceil(to_pos.x / node_density)][(int)ceil(to_pos.y / node_density)];
	std::vector<Node> open_list;
	std::vector<Node> closed_list;

	open_list.push_back(node_grid[(int)ceil(from_pos.x / node_density)][(int)ceil(from_pos.y / node_density)]);

	while (!open_list.empty())
	{
		Node current_node = open_list[0];

		int ind = 0;
		for (int i = 1; i < open_list.size(); i++)
		{
			if ((open_list[i].FCost() < current_node.FCost() || open_list[i].FCost() == current_node.FCost()) && open_list[i].HCost() < current_node.HCost())
			{
				current_node = open_list[i];
				ind = i;
			}
		}

		open_list.erase(open_list.begin() + ind);
		closed_list.push_back(current_node);

		if (current_node.Pos().x == end_node.Pos().x &&
			current_node.Pos().y == end_node.Pos().y)
		{
			return FinalPath(current_node, end_node);
		}

		//std::vector<Node> neighbours = Neighbours(current_node);
		//for (int i = 0; i < neighbours.size(); i++)
		//{
		//	if (!neighbours[i].Pathable())
		//	{
		//		continue;
		//	}
		//	bool in_closed = false;
		//	for (int j = 0; j < closed_list.size(); j++)
		//	{
		//		if (neighbours[i].Pos().x == closed_list[j].Pos().x &&
		//			neighbours[i].Pos().y == closed_list[j].Pos().y)
		//		{
		//			in_closed = true;
		//			break;
		//		}
		//	}
		//	if (in_closed)
		//	{
		//		continue;
		//	}
		//	bool in_open = false;
		//	for (int j = 0; j < open_list.size(); j++)
		//	{
		//		if (neighbours[i].Pos().x == open_list[j].Pos().x &&
		//			neighbours[i].Pos().y == open_list[j].Pos().y)
		//		{
		//			in_open = true;
		//			break;
		//		}
		//	}
		//	int move_cost = current_node.GCost() + ManhattenDistance(current_node, end_node);
		//	if (!in_open || move_cost < neighbours[i].GCost())
		//	{
		//		neighbours[i].GCost() = move_cost;
		//		neighbours[i].HCost() = ManhattenDistance(neighbours[i], end_node);
		//		neighbours[i].SetParent(current_node);
		//		if (!in_open)
		//		{
		//			open_list.push_back(neighbours[i]);
		//		}
		//	}
		//}
	}
}

std::vector<Node> Grid::FinalPath(Node start_node, Node end_node)
{
	std::vector<Node> path;
	Node current_node = end_node;

	while (current_node.Pos().x != end_node.Pos().x &&
		current_node.Pos().y != end_node.Pos().y)
	{
		path.insert(path.begin(), current_node);
		current_node = current_node.GetParent();
	}

	return path;
}

int Grid::ManhattenDistance(Node start, Node end)
{
	int x_dist = abs(start.Pos().x - end.Pos().y);
	int y_dist = abs(start.Pos().x - end.Pos().y);
	return x_dist + y_dist;
}

std::vector<Node> Grid::Neighbours(Node node)
{
	std::vector<Node> neighbours;
	if (node.Pos().x >= 0 && node.Pos().x < grid_size.x &&
		node.Pos().y + 1 >= 0 && node.Pos().y + 1 < grid_size.y)
	{
		neighbours.push_back(node_grid[(int)node.Pos().x][(int)node.Pos().y + 1]);
	}
	if (node.Pos().x + 1 >= 0 && node.Pos().x + 1 < grid_size.x &&
		node.Pos().y + 1 >= 0 && node.Pos().y + 1 < grid_size.y)
	{
		neighbours.push_back(node_grid[(int)node.Pos().x + 1][(int)node.Pos().y + 1]);
	}
	if (node.Pos().x + 1 >= 0 && node.Pos().x + 1 < grid_size.x &&
		node.Pos().y >= 0 && node.Pos().y < grid_size.y)
	{
		neighbours.push_back(node_grid[(int)node.Pos().x + 1][(int)node.Pos().y]);
	}
	if (node.Pos().x + 1 >= 0 && node.Pos().x + 1 < grid_size.x &&
		node.Pos().y - 1 >= 0 && node.Pos().y - 1 < grid_size.y)
	{
		neighbours.push_back(node_grid[(int)node.Pos().x + 1][(int)node.Pos().y - 1]);
	}
	if (node.Pos().x >= 0 && node.Pos().x < grid_size.x &&
		node.Pos().y - 1 >= 0 && node.Pos().y - 1 < grid_size.y)
	{
		neighbours.push_back(node_grid[(int)node.Pos().x][(int)node.Pos().y - 1]);
	}
	if (node.Pos().x - 1 >= 0 && node.Pos().x - 1 < grid_size.x &&
		node.Pos().y - 1 >= 0 && node.Pos().y - 1 < grid_size.y)
	{
		neighbours.push_back(node_grid[(int)node.Pos().x - 1][(int)node.Pos().y - 1]);
	}
	if (node.Pos().x - 1 >= 0 && node.Pos().x - 1 < grid_size.x &&
		node.Pos().y >= 0 && node.Pos().y < grid_size.y)
	{
		neighbours.push_back(node_grid[(int)node.Pos().x - 1][(int)node.Pos().y]);
	}
	if (node.Pos().x - 1 >= 0 && node.Pos().x - 1 < grid_size.x &&
		node.Pos().y + 1 >= 0 && node.Pos().y + 1 < grid_size.y)
	{
		neighbours.push_back(node_grid[(int)node.Pos().x - 1][(int)node.Pos().y + 1]);
	}

	return neighbours;
}