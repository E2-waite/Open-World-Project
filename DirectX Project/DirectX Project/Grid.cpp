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
			grid[x][y] = 0;
		}
	}
}

std::vector<Node> Grid::MakePath(XMINT2 from_pos, XMINT2 to_pos)
{
	if (from_pos.x > (CHUNKS_X * NODE_DENSITY) - 1 || from_pos.y > (CHUNKS_Y * NODE_DENSITY) - 1 ||
		from_pos.x < 0 || from_pos.y < 0)
	{
		// Deletes transform file if value is read wrong (strange bug rarely occurs causing NPC position to be set to really high value)
		remove((char*)&TRANSFORMATION_FILE);
	}

	Node node_grid[CHUNKS_X * NODE_DENSITY][CHUNKS_Y * NODE_DENSITY];

	for (int x = 0; x < grid_size.x; x++)
	{
		for (int y = 0; y < grid_size.y; y++)
		{
			node_grid[x][y].Pos() = XMINT2(x, y);
		}
	}



	Node end_node = node_grid[(int)ceil(to_pos.x / NODE_DENSITY)][(int)ceil(to_pos.y / NODE_DENSITY)];
	Node start_node = node_grid[(int)ceil(from_pos.x / NODE_DENSITY)][(int)ceil(from_pos.y / NODE_DENSITY)];
	std::vector<Node> open_list;
	std::vector<Node> closed_list;

	open_list.push_back(start_node);

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
			std::vector<Node> nodes;
			while (current_node.HasParent())
			{
				nodes.insert(nodes.begin(), current_node);
				current_node = current_node.GetParent();
			}
			XMINT2 start_pos = start_node.Pos();
			XMINT2 end_pos = end_node.Pos();
			return nodes;
		}

		std::vector<Node> neighbours;
		for (int i = 0; i < DIRECTIONS; i++)
		{
			if (Valid(XMINT2(current_node.Pos().x + dx[i], current_node.Pos().y + dy[i])))
			{
				neighbours.push_back(node_grid[current_node.Pos().x + dx[i]][current_node.Pos().y + dy[i]]);
			}
		}
		for (int i = 0; i < neighbours.size(); i++)
		{
			bool in_closed = false;
			for (int j = 0; j < closed_list.size(); j++)
			{
				if (neighbours[i].Pos().x == closed_list[j].Pos().x &&
					neighbours[i].Pos().y == closed_list[j].Pos().y)
				{
					in_closed = true;
					break;
				}
			}
			if (in_closed)
			{
				continue;
			}
			bool in_open = false;
			for (int j = 0; j < open_list.size(); j++)
			{
				if (neighbours[i].Pos().x == open_list[j].Pos().x &&
					neighbours[i].Pos().y == open_list[j].Pos().y)
				{
					in_open = true;
					break;
				}
			}
			int move_cost = current_node.GCost() + ManhattenDistance(current_node, end_node);
			if (!in_open || move_cost < neighbours[i].GCost())
			{
				neighbours[i].GCost() = move_cost;
				neighbours[i].HCost() = ManhattenDistance(neighbours[i], end_node);
				neighbours[i].SetParent(current_node);
				if (!in_open)
				{
					open_list.push_back(neighbours[i]);
				}
			}
		}
	}
	std::vector<Node> empty;
	return empty;
}

int Grid::ManhattenDistance(Node start, Node end)
{
	int x_dist = abs(start.Pos().x - end.Pos().y);
	int y_dist = abs(start.Pos().x - end.Pos().y);
	return x_dist + y_dist;
}

bool Grid::Valid(XMINT2 pos)
{
	if (pos.x >= 0 && pos.x < grid_size.x &&
		pos.y + 1 >= 0 && pos.y + 1 < grid_size.y &&
		grid[pos.x][pos.y] == 0)
	{
		return true;
	}
	return false;
}
