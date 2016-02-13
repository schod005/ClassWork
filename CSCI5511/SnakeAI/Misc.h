#include <SFML/Graphics.hpp>
#include <queue>
#include "Constants.h"
#ifndef MISC_HPP
#define MISC_HPP
int sfVecToInt(sf::Vector2i vec)
{
	return vec.x + GRID_SIZE * vec.y;
}

sf::Vector2i intTosfVec(int num)
{
	if (num >= GRID_SIZE)
		return sf::Vector2i(num % GRID_SIZE, num / GRID_SIZE);
	else
		return sf::Vector2i(num, 0);
}

inline double heuristic(sf::Vector2i Loc1, sf::Vector2i Loc2)
{
	//return 0;
	//return abs(Loc1.x - Loc2.x) + abs(Loc1.y - Loc2.y);
	return sqrt(pow(abs(Loc1.x - Loc2.x), 2) + pow(abs(Loc1.y - Loc2.y), 2)) + abs(Loc1.x - Loc2.x) + abs(Loc1.y - Loc2.y);
}

template <class T> struct greater1
{
	bool operator() (const T& a, const T& b) const { return a.first > b.first; }
};

struct PriorityQueue{
	typedef std::pair<int, sf::Vector2i> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>,
						greater1<PQElement>> elements;

	inline bool empty() { return elements.empty(); }

	inline void put(sf::Vector2i item, int priority)
	{
		elements.emplace(priority, item);
	}

	inline sf::Vector2i get()
	{
		sf::Vector2i best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

bool boundary_check(int move, sf::Vector2i location)
{
	if ((location.x == 0 && move == LEFT))
		return false;
	else if ((location.x == GRID_SIZE - 1 && move == RIGHT))
		return false;
	else if ((location.y == 0 && move == UP))
		return false;
	else if ((location.y == GRID_SIZE - 1 && move == DOWN))
		return false;
	return true;
}


#endif