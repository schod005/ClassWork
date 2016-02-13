#ifndef GRID_HPP
#define GRID_HPP
//SFML Headers
#include <SFML/Graphics.hpp>

//Project Headers
#include "Constants.h"
#include "Misc.h"

//System Headers
#include <iostream>
#include <functional>
#include <unordered_map>
#include <stdint.h>


class Grid
{
public:
	Grid();
	Grid(int, int);
	~Grid();
	void draw(sf::RenderWindow&);
	void generateApple();
	std::vector<sf::Vector2i> neighbors(sf::Vector2i Loc);
	int aStarSearch(sf::Vector2i currentLoc, sf::Vector2i destLoc);
	int depthFirstSearch(sf::Vector2i currentLoc, sf::Vector2i destLoc);
	bool dfs(sf::Vector2i currentLoc, sf::Vector2i destLoc, std::unordered_map<int, int>& came_from, bool** visited);
	std::vector<sf::Vector2i> reconstruct_path(sf::Vector2i& currentLoc, sf::Vector2i& destLoc, std::unordered_map<int, int>&);

	inline int getRows(){ return rows; }
	inline int getCols(){ return cols; }
	inline sf::RectangleShape **getDrawGrid(){ return drawGrid; }
	inline sf::Vector2i getAppleLoc(){ return appleLoc; }
	inline int64_t getNodesExpanded(){ return nodes_expanded; }

private:
	std::vector <sf::Vector2i> dfsPathArray;
	int dfsPath;
	int rows;
	int cols;
	sf::RectangleShape **drawGrid;
	sf::Vector2i appleLoc;
	bool applegen;
	int64_t nodes_expanded;

};

#endif

Grid::Grid()
{
	//empty
}

Grid::Grid(int cols_, int rows_)
{
	rows = rows_;
	cols = cols_;
	dfsPath = 0;
	nodes_expanded = 0;


	drawGrid = new sf::RectangleShape*[rows];
	for (int i = 0; i < rows; i++)
	{
		drawGrid[i] = new sf::RectangleShape[cols];
	}

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			drawGrid[i][j].setSize(sf::Vector2f((float)WINDOW_WIDTH / rows - 2,
											    (float)WINDOW_HEIGHT / cols - 2));
			drawGrid[i][j].setPosition(sf::Vector2f((float)i * WINDOW_WIDTH / rows + 1,
													(float)j * WINDOW_HEIGHT / cols + 1));
			drawGrid[i][j].setFillColor(sf::Color(140, 140, 140, 255));
			
		}

	//adding a random apple at start of creation
//	for (int yy = 1; yy < GRID_SIZE; yy+=4)
//		for (int xx = 1; xx < GRID_SIZE; xx += 4)
//			for (int i = xx; i < 2 + xx && i < GRID_SIZE; i++)
//				for (int j = yy; j < 2 + yy && j < GRID_SIZE; j++)
//					drawGrid[i][j].setFillColor(sf::Color::Magenta);
	generateApple();
}

Grid::~Grid()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] drawGrid[i];
	}
	delete[] drawGrid;
}

//Draws the grid
void Grid::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			window.draw(drawGrid[i][j]);
		}
}

//Generates a new random locations for the apple
void Grid::generateApple()
{
	int rand_row = rand() % rows;
	int rand_col = rand() % cols;

	while (drawGrid[rand_col][rand_row].getFillColor() == sf::Color::Black ||
		   drawGrid[rand_col][rand_row].getFillColor() == sf::Color::Green ||
		   drawGrid[rand_col][rand_row].getFillColor() == sf::Color::Magenta)
	{
		rand_row = rand() % rows;
		rand_col = rand() % cols;
	}


	appleLoc.x = rand_col;
	appleLoc.y = rand_row;

	drawGrid[appleLoc.x][appleLoc.y].setFillColor(sf::Color::Red);
	applegen = true;
}

//returns a list of neighboring nodes
std::vector<sf::Vector2i> Grid::neighbors(sf::Vector2i Loc)
{
  std::vector<sf::Vector2i> list;
  if(Loc.x - 1 >= 0 && (drawGrid[Loc.x - 1][Loc.y].getFillColor() == sf::Color(140,140,140,255) ||
						drawGrid[Loc.x - 1][Loc.y].getFillColor() == sf::Color::Red ||
						drawGrid[Loc.x - 1][Loc.y].getFillColor() == sf::Color::Blue))
    list.emplace_back(sf::Vector2i(Loc.x - 1, Loc.y));
  if(Loc.x + 1 < GRID_SIZE && (drawGrid[Loc.x + 1][Loc.y].getFillColor() == sf::Color(140,140,140,255) || 
							   drawGrid[Loc.x + 1][Loc.y].getFillColor() == sf::Color::Red ||
							   drawGrid[Loc.x + 1][Loc.y].getFillColor() == sf::Color::Blue))
    list.emplace_back(sf::Vector2i(Loc.x + 1, Loc.y));
  if(Loc.y - 1 >= 0 && (drawGrid[Loc.x][Loc.y - 1].getFillColor() == sf::Color(140,140,140,255) || 
						drawGrid[Loc.x][Loc.y - 1].getFillColor() == sf::Color::Red ||
						drawGrid[Loc.x][Loc.y - 1].getFillColor() == sf::Color::Blue))
    list.emplace_back(sf::Vector2i(Loc.x, Loc.y - 1));
  if(Loc.y + 1 < GRID_SIZE && (drawGrid[Loc.x][Loc.y + 1].getFillColor() == sf::Color(140,140,140,255) || 
							   drawGrid[Loc.x][Loc.y + 1].getFillColor() == sf::Color::Red ||
							   drawGrid[Loc.x][Loc.y + 1].getFillColor() == sf::Color::Blue))
    list.emplace_back(sf::Vector2i(Loc.x, Loc.y + 1));
  return list;
}

//Finds a path from currentLoc to destLoc using A* algorithm
int Grid::aStarSearch(sf::Vector2i currentLoc, sf::Vector2i destLoc)
{
	PriorityQueue frontier;
	frontier.put(currentLoc, 0);

	std::unordered_map<int, int> came_from;
	std::unordered_map<int, int> cost_so_far;

	came_from[sfVecToInt(currentLoc)] = sfVecToInt(currentLoc);
	cost_so_far[sfVecToInt(currentLoc)] = 0;

	while (!frontier.empty())
	{
		auto current = frontier.get();
		if (current == destLoc)
		{
			break;
		}

		for (auto next : neighbors(current))
		{
			if (next != destLoc)
			{
				drawGrid[next.x][next.y].setFillColor(sf::Color::Blue);
				nodes_expanded++;
			}
			int new_cost = cost_so_far[sfVecToInt(current)] + 1;
			if (!cost_so_far.count(sfVecToInt(next)) || new_cost < cost_so_far[sfVecToInt(next)])
			{
				cost_so_far[sfVecToInt(next)] = new_cost;
				int priority = new_cost + heuristic(next, destLoc);
				frontier.put(next, priority);
				came_from[sfVecToInt(next)] = sfVecToInt(current);
			}
		}
	}
	std::vector <sf::Vector2i> path = reconstruct_path(currentLoc, destLoc, came_from);

	applegen = false;
	if (path[0].x == -1)
		return -1;
	sf::Vector2i next = path[1];
	if (currentLoc.x - next.x == -1)
		return RIGHT;
	if (currentLoc.x - next.x == 1)
		return LEFT;
	if (currentLoc.y - next.y == -1)
		return DOWN;
	if (currentLoc.y - next.y == 1)
		return UP;
	return -1;
}

//Helper function used to recursively find a path for depth-first search
bool Grid::dfs(sf::Vector2i currentLoc, sf::Vector2i destLoc, std::unordered_map<int, int>& came_from, bool **visited)
{
	std::vector<sf::Vector2i> neighbor = neighbors(currentLoc);
	for (int i = neighbor.size() ? rand() % neighbor.size() : neighbor.size(), j = 0; j < neighbor.size(); j++, i >= neighbor.size() - 1 ? i = 0 : i++)
	{	
		drawGrid[neighbor[i].x][neighbor[i].y].setFillColor(sf::Color::Blue);
		nodes_expanded++;
		if (visited[neighbor[i].x][neighbor[i].y] == true)
			continue;
		visited[neighbor[i].x][neighbor[i].y] = true;
		came_from[sfVecToInt(neighbor[i])] = sfVecToInt(currentLoc); 
		if (neighbor[i] + sf::Vector2i(0,1) == destLoc)
		{
			came_from[sfVecToInt(destLoc)] = sfVecToInt(neighbor[i]);
			return true;
		}
		if (neighbor[i] + sf::Vector2i(1,0) == destLoc)
		{
			came_from[sfVecToInt(destLoc)] = sfVecToInt(neighbor[i]);
			return true;
		}
		if (neighbor[i] + sf::Vector2i(-1,0) == destLoc)
		{
			came_from[sfVecToInt(destLoc)] = sfVecToInt(neighbor[i]);
			return true;
		}
		if (neighbor[i] + sf::Vector2i(0,-1) == destLoc)
		{
			came_from[sfVecToInt(destLoc)] = sfVecToInt(neighbor[i]);
			return true;
		}
		else if (dfs(neighbor[i], destLoc, came_from, visited))
		{
			return true;
		}
	}
	return false;
}

//Finds a path from currentLoc to destLoc using depth-first search
int Grid::depthFirstSearch(sf::Vector2i currentLoc, sf::Vector2i destLoc)
{
	if (!dfsPath)
	{
		PriorityQueue frontier;
		frontier.put(currentLoc, 0);

		std::unordered_map<int, int> came_from;

		came_from[sfVecToInt(currentLoc)] = sfVecToInt(currentLoc);
		bool **visited = new bool*[GRID_SIZE];
		for (int i = 0; i < GRID_SIZE; i++)
		{
			visited[i] = new bool[GRID_SIZE];
			for (int j = 0; j < GRID_SIZE; j++)
				visited[i][j] = false;
		}
		if (!dfs(currentLoc, destLoc, came_from, visited))
			return -123;
		for (int i = 0; i < GRID_SIZE; i++)
			delete[] visited[i];
		delete[] visited;

		dfsPathArray = reconstruct_path(currentLoc, destLoc, came_from);

		if (dfsPathArray[0].x == -1)
			return -1;
		dfsPath = 2;
		sf::Vector2i next = dfsPathArray[1];
		if (currentLoc.x - next.x == -1)
			return RIGHT;
		if (currentLoc.x - next.x == 1)
			return LEFT;
		if (currentLoc.y - next.y == -1)
			return DOWN;
		if (currentLoc.y - next.y == 1)
			return UP;
		return -1;
	}
	else
	{
		sf::Vector2i next = dfsPathArray[dfsPath];
		dfsPath++;
		if (next == destLoc)
			dfsPath = 0;
		if (currentLoc.x - next.x == -1)
			return RIGHT;
		if (currentLoc.x - next.x == 1)
			return LEFT;
		if (currentLoc.y - next.y == -1)
			return DOWN;
		if (currentLoc.y - next.y == 1)
			return UP;
		return -1;
	}

}

//constructs a path from currentLoc to destLoc, coloring all nodes along the path yellow
std::vector<sf::Vector2i> Grid::reconstruct_path(sf::Vector2i& currentLoc, sf::Vector2i& destLoc, std::unordered_map<int, int>& came_from)
{
	std::vector<sf::Vector2i> path;
	sf::Vector2i current = destLoc;
	path.push_back(current);
	int count = 0;
	while (current != currentLoc)
	{
		count++;
		if (count > GRID_SIZE * GRID_SIZE)
		{
			std::cout << "DEAD!!" << std::endl;
			path[0].x = -1;
			break;
		}
		current = intTosfVec(came_from[sfVecToInt(current)]);
		path.push_back(current);
	}
	if (path[0].x != -1)
	{
		std::reverse(path.begin(), path.end());
		for (int i = 1; i < path.size() - 1; i++)
		{
			drawGrid[path[i].x][path[i].y].setFillColor(sf::Color::Yellow);
		}
	}
	return path;
}
