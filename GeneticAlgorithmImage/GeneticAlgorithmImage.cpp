#pragma once
#include <SFML/Graphics.hpp>
#include "GeneticImage.h"
#include "ImageHash.h"
int main()
{
	int width = 720;
	int height = 480;

	sf::RenderWindow window(sf::VideoMode(width, height), "Genetic image Evolution");
	window.setFramerateLimit(60);

	sf::Image refImage;
	refImage.create(width / 2, height);
	
	ImageHash imgHash;

	sf::Image monaLisaImage;
	monaLisaImage.loadFromFile("./img/mona_lisa2.jpg");

	sf::Texture monaLisaTexture;
	monaLisaTexture.loadFromImage(monaLisaImage);

	sf::RectangleShape monaLisaRect;
	monaLisaRect.setTexture(&monaLisaTexture);
	monaLisaRect.setSize(sf::Vector2f(width / 2, height));
	monaLisaRect.setPosition(width / 2, 0);

	sf::RenderTexture rt;
	rt.create(width / 2, height);
	rt.draw(monaLisaRect);

	GeneticImage genImg(10, rt.getTexture().copyToImage());

	GeneticImage currentImg = genImg.copy();

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

		sf::Sprite sprite;
		currentImg.render();
		sprite.setTexture(currentImg.getTexture());

		window.clear();

		window.draw(sprite);
		window.draw(monaLisaRect);

		window.display();

		currentImg = currentImg.getMutadedCopy(0.1f);
	}


	return 0;
}