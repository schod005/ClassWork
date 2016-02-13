//SFML Headers
#include <SFML/Graphics.hpp>

//Project Headers
#include "Constants.h"
#include "Grid.h"
#include "Snake.h"

//System Headers
#include <iostream>
#include <iomanip>


time_t now = 0, then = 0;
int frames = 0;
void FPS();
int init = 0;

int main()
{
  srand(time(0));
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
  if (!font.loadFromFile("arial.ttf"))
	  return 0;
  //window.setFramerateLimit(60);
  WINDOW_HANDLE = &window;
  Grid *grid = new Grid(GRID_SIZE, GRID_SIZE);
  Snake *snake1 = new Snake(grid, 0, 0, 1);
//  Snake *snake2 = new Snake(grid, GRID_SIZE - 1, GRID_SIZE - 1, 2);
//   Snake *snake3 = new Snake(grid, GRID_SIZE - 1, 0, 3);
//   Snake *snake4 = new Snake(grid, 0, GRID_SIZE - 1, 4);
 

  while (window.isOpen())
  {
    FPS();
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
	for (int i = 0; i < GRID_SIZE; i++)
		for (int j = 0; j < GRID_SIZE; j++)
			if (grid->getDrawGrid()[i][j].getFillColor() == sf::Color::Yellow || grid->getDrawGrid()[i][j].getFillColor() == sf::Color::Blue)
				grid->getDrawGrid()[i][j].setFillColor(sf::Color(140, 140, 140, 255));
    window.clear();
    snake1->aStarMove();
//    snake2->depthFirstMove();
//     snake3->randMove();
//     snake4->randMove();
    grid->draw(window);
	snake1->drawText();
//	snake2->drawText();
//	snake3->drawText();
//	snake4->drawText();
    window.display();			

	sf::sleep(sf::Time(sf::milliseconds(100)));            //adding some delay to see snake move


  }

  return 0;
}

void FPS()
{
  then = now;
  now = time(0);
  frames++;
  if (now != then)
  {
    std::cout << std::setw(5) << frames << " FPS\r" << std::flush;
    frames = 0;
  }
}
