#include <SFML/Graphics.hpp>

int main()
{

	int width = 512;
	int height = 512;

	sf::RenderWindow window(sf::VideoMode(width, height), "RGB to Lab");
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
			default:
				break;
			}
		}

		window.clear();
		window.display();
	}

	return 0;
}