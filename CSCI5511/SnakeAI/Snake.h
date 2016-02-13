#ifndef SNAKE_HPP
#define SNAKE_HPP
//Project Headers
#include "Constants.h"
#include "Misc.h"


class Snake
{
public:
	Snake();
	Snake(Grid*, int x, int y, int number);
	void update(int);
	int randMove();
	void aStarMove();
	void depthFirstMove();
	bool checkApple(int);
	void drawText() {WINDOW_HANDLE->draw(text);}
	
	inline int getLength(){ return length; }


private:
	int length;
	int number;
	sf::Text text;
	Grid* GRID;
	struct Node
	{
		Node* next;
		Node* prev;
		sf::Vector2i location;
	}*head;

	Node *tail;
};

#endif

Snake::Snake()
{
	//empty
}

Snake::Snake(Grid* Grid_, int x, int y, int number_)
{
	number = number_;
	text.setFont(font);
	text.setString(std::to_string(number));
	text.setColor(sf::Color::Magenta);
	text.setCharacterSize(20);
	length = 1;
	head = new Node;
	head->next = nullptr;
	head->prev = nullptr;
	head->location.x = x;
	head->location.y = y;
	tail = head;

	GRID = Grid_;
	GRID->getDrawGrid()[x][y].setFillColor(sf::Color::Black);
}

//randomly moves the snake
int Snake::randMove()
{
	//0 move left
	//1 move up
	//2 move right
	//3 move down
	for (int i = 0; i < GRID_SIZE; i++)
		for (int j = 0; j < GRID_SIZE; j++)
			if (GRID->getDrawGrid()[i][j].getFillColor() == sf::Color::Yellow)
				GRID->getDrawGrid()[i][j].setFillColor(sf::Color(140, 140, 140, 255));
	int move;

	//testing if we are sitting on boundary cases elminating those movements
	if ((head->location.x == 0) && (head->location.y == 0))                    //move right if at top left corner
		move = RIGHT;
	else if ((head->location.x == GRID->getCols() - 1) && (head->location.y == 0))        //move down if at top right corner
		move = DOWN;
	else if ((head->location.x == GRID->getCols() - 1) && (head->location.y == GRID->getRows() - 1)) //move left if at bottum right corner
		move = LEFT;
	else if ((head->location.x == 0) && (head->location.y == GRID->getRows() - 1))        //move up if bottum left corner
		move = UP;
	else if ((head->location.x == 0))
		move = RIGHT;
	else if ((head->location.x == GRID->getCols() - 1))
		move = DOWN;
	else if ((head->location.y == 0))
		move = DOWN;
	else if ((head->location.y == GRID->getRows() - 1))
		move = UP;
	else
		move = rand() % 4;

	int count = 0;
	while (true)
	{
		count++;
		if (count > 50)
		{
			return -1;
		}
		if (move == UP)
		{
			if (!boundary_check(move, head->location))
			{
				move = rand() % 4;
			}
			else if (GRID->getDrawGrid()[head->location.x][head->location.y - 1].getFillColor() != sf::Color(140, 140, 140, 255) &&
				GRID->getDrawGrid()[head->location.x][head->location.y - 1].getFillColor() != sf::Color::Red)
			{
				move = rand() % 4;
			}
			else
				break;
		}
		if (move == DOWN)
		{
			if (!boundary_check(move, head->location))
			{
				move = rand() % 4;
			}
			else if (GRID->getDrawGrid()[head->location.x][head->location.y + 1].getFillColor() != sf::Color(140, 140, 140, 255) &&
				GRID->getDrawGrid()[head->location.x][head->location.y + 1].getFillColor() != sf::Color::Red)
			{
				move = rand() % 4;
			}
			else
				break;
		}
		if (move == LEFT)
		{
			if (!boundary_check(move, head->location))
			{
				move = rand() % 4;
			}
			else if (GRID->getDrawGrid()[head->location.x - 1][head->location.y].getFillColor() != sf::Color(140, 140, 140, 255) &&
				GRID->getDrawGrid()[head->location.x - 1][head->location.y].getFillColor() != sf::Color::Red)
			{
				move = rand() % 4;
			}
			else
				break;
		}
		if (move == RIGHT)
		{
			if (!boundary_check(move, head->location))
			{
				move = rand() % 4;
			}
			else if (GRID->getDrawGrid()[head->location.x + 1][head->location.y].getFillColor() != sf::Color(140, 140, 140, 255) &&
				GRID->getDrawGrid()[head->location.x + 1][head->location.y].getFillColor() != sf::Color::Red)
			{
				move = rand() % 4;
			}
			else
				break;
		}
	}

	update(move);
	//GRID->aStarSearch(head->location, GRID->getAppleLoc());
	return 0;
}

//moves the snake according to the A* algorithm
void Snake::aStarMove()
{
	int move = GRID->aStarSearch(head->location, GRID->getAppleLoc());
	if (move != -1 && move != -123)
	{
		update(move);
	}
	else
	{
		for (int i = 0; i < GRID_SIZE; i++)
			for (int j = 0; j < GRID_SIZE; j++)
				if (GRID->getDrawGrid()[i][j].getFillColor() == sf::Color::Yellow || GRID->getDrawGrid()[i][j].getFillColor() == sf::Color::Blue)
					GRID->getDrawGrid()[i][j].setFillColor(sf::Color(140, 140, 140, 255));
		if (randMove() == -1)
		{
			std::cout << "GAME OVER!! Snake Length: " << length << " Nodes Expanded: " << GRID->getNodesExpanded() << std::endl;
			sf::sleep(sf::Time(sf::seconds(100)));
		}
	}
}

//moves the snake according to the depth-first search algorithm
void Snake::depthFirstMove()
{
	int move = GRID->depthFirstSearch(head->location, GRID->getAppleLoc());
	if (move != -1 && move != -123)
	{
		update(move);
	}
	else
	{
		for (int i = 0; i < GRID_SIZE; i++)
			for (int j = 0; j < GRID_SIZE; j++)
				if (GRID->getDrawGrid()[i][j].getFillColor() == sf::Color::Yellow || GRID->getDrawGrid()[i][j].getFillColor() == sf::Color::Blue)
					GRID->getDrawGrid()[i][j].setFillColor(sf::Color(140, 140, 140, 255));
		if (randMove() == -1)
		{
			std::cout << "GAME OVER!! Snake Length: " << length << " Nodes Expanded: " << GRID->getNodesExpanded() << std::endl;
			sf::sleep(sf::Time(sf::seconds(100)));
		}
	}
}

//updates positioning of the snake
void Snake::update(int move)
{
	if (checkApple(move))
	{
		//if apple is eaten, add a new head at its location
		GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Black);
		Node* newHead = new Node;
		newHead->next = head;
		newHead->prev = nullptr;
		head->prev = newHead;

		switch (move)
		{
		case UP:
			newHead->location.x = head->location.x;
			newHead->location.y = head->location.y - 1;
			break;
		case DOWN:
			newHead->location.x = head->location.x;
			newHead->location.y = head->location.y + 1;
			break;
		case LEFT:
			newHead->location.x = head->location.x - 1;
			newHead->location.y = head->location.y;
			break;
		case RIGHT:
			newHead->location.x = head->location.x + 1;
			newHead->location.y = head->location.y;
			break;
		default:
			break;
		}
		head = newHead;
		length++;

		GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Green);
		GRID->generateApple();
	}
	else
	{
		if (length == 1)
		{
			//if length is 1, head and tail are pointing at the same thing, so just move head
			GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color(140, 140, 140, 255));
			switch (move)
			{
			case UP:
				head->location.y--;
				break;
			case DOWN:
				head->location.y++;
				break;
			case LEFT:
				head->location.x--;
				break;
			case RIGHT:
				head->location.x++;
				break;
			default:
				break;
			}
			GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Green);
		}
		else
		{
			//update colors and move tail to location of move
			GRID->getDrawGrid()[tail->location.x][tail->location.y].setFillColor(sf::Color(140, 140, 140, 255));
			GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Black);

			Node* tempTail = tail;
			tail = tail->prev;
			tempTail->prev->next = nullptr;
			tempTail->prev = nullptr;
			tempTail->next = head;
			head->prev = tempTail;
			head = tempTail;

			switch (move)
			{
			case UP:
				head->location.y = head->next->location.y - 1;
				head->location.x = head->next->location.x;
				break;
			case DOWN:
				head->location.y = head->next->location.y + 1;
				head->location.x = head->next->location.x;
				break;
			case LEFT:
				head->location.y = head->next->location.y;
				head->location.x = head->next->location.x - 1;
				break;
			case RIGHT:
				head->location.y = head->next->location.y;
				head->location.x = head->next->location.x + 1;
				break;
			default:
				break;
			}
			GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Green);
		}
	}

	text.setPosition(GRID->getDrawGrid()[head->location.x][head->location.y].getPosition());
	text.setString(std::to_string(number) + "\n" + std::to_string(length));
}

//checks if the apple is located at the location the snake will move
bool Snake::checkApple(int move)
{
	sf::Vector2i appleLoc = GRID->getAppleLoc();

	switch (move)
	{
	case UP:
		if (appleLoc.x == head->location.x && appleLoc.y == head->location.y - 1)
			return true;
		break;
	case DOWN:
		if (appleLoc.x == head->location.x && appleLoc.y == head->location.y + 1)
			return true;
		break;
	case LEFT:
		if (appleLoc.x == head->location.x - 1 && appleLoc.y == head->location.y)
			return true;
		break;
	case RIGHT:
		if (appleLoc.x == head->location.x + 1 && appleLoc.y == head->location.y)
			return true;
		break;
	default:
		return false;
	}
	return false;
}