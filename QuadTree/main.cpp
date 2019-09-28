#include <sfml/Graphics.hpp>

int main()
{
	unsigned int width = 512;
	unsigned int height = 512;

	sf::RenderWindow window(sf::VideoMode(width, height), "QuadTree");
	window.setFramerateLimit(60);

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
			}
		}

		window.clear();
		window.display();
	}

	return 0;
}