#include <SFML/Graphics.hpp>
#ifndef CONSTANTS_H
#define CONSTANTS_H

static int WINDOW_WIDTH = 800;
static int WINDOW_HEIGHT = 800;
static sf::RenderWindow *WINDOW_HANDLE;
static sf::Font font;
#define GRID_SIZE 20

enum{
	LEFT = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3
};



#endif
