#include <SFML/Graphics.hpp>
#include "Sudoku.h"

int main()
{

	int width = 512;
	int height = 512;

	sf::RenderWindow window(sf::VideoMode(width, height), "Sudoku Generator");
	window.setFramerateLimit(60);


	Sudoku sudoku(width / 2.0f, height / 2.0f, width, height);

	unsigned int counter = 0;
	sf::Event evnt;
	while (window.isOpen())
	{
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		window.clear();
		sudoku.t_testSprite(&window, (counter / 60) % 10);
		window.display();
		counter++;
	}

	return 0;
}