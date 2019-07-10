#include <cstdio>
#include <SFML/Graphics.hpp>

int main()
{
	int width = 512;
	int height = 512;

	int iterPerFrame = 100;
	const int resolution = 100;
	int x = resolution / 2;
	int y = resolution / 2;
	int r = 0;
	unsigned int c[resolution][resolution]{0};

	/*for (int i = 0; i < 4; i++)
	{
		r = (r - 1 + (c[x][y] * 2)) % 4;
		c[x][y] = !c[x][y];
		x += (r % 2) * (2 - r);
		y += ((r + 1) % 2) * (-1 + ((r + 1) % 2) * r);
	}*/
	
	sf::RenderWindow window(sf::VideoMode(width, height), "Langton's ant");
	window.setFramerateLimit(60);

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(
		static_cast<float>(width) / static_cast<float>(resolution),
		static_cast<float>(height) / static_cast<float>(resolution)));
	//rect.setOrigin(rect.getSize());
	rect.setFillColor(sf::Color::White);
	rect.setOutlineColor(sf::Color(128,128,128));
	rect.setOutlineThickness(0.5f);
	rect.setScale(0.8f, 0.8f);

	window.clear();
	float x_offset = static_cast<float>(width) / 2.0f;
	float y_offset = static_cast<float>(height) / 2.0f;
	float x_mult = static_cast<float>(width) / static_cast<float>(resolution);
	float y_mult = static_cast<float>(height) / static_cast<float>(resolution);
	
	bool firstFrame = true;


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

			for (int i = 0; i < iterPerFrame; i++)
			{
				r = (r - 1 + (c[x][y] * 2)) % 4;
				c[x][y] = !c[x][y];
				y += (r % 2) * (2 - r);
				x += ((r + 1) % 2) * (-1 + ((r + 1) % 2) * r);
				if (y < 0)
					int a = 0;
			}
		

		window.clear();
		for (int ry = 0; ry < resolution; ry++)
		{
			for (int rx = 0; rx < resolution; rx++)
			{
				if (c[rx][ry] == true)
				{
					rect.setFillColor(sf::Color::Black);
				}
				else
				{
					rect.setFillColor(sf::Color::White);
				}
				if (rx == x && ry == y)
					rect.setFillColor(sf::Color::Red);

				rect.setPosition(rx * x_mult, ry * y_mult);
				window.draw(rect);
			}
		}
		window.display();
	}


	return 0;
}