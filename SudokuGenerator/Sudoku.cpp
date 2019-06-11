#include "Sudoku.h"

#include <string>

Sudoku::Sudoku(float x, float y, float width, float height)
{
	setPos(x, y);
	setSize(width, height);
	m_generateNumberSprites();
}

void Sudoku::setPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void Sudoku::setSize(float width, float height)
{
	m_size.x = width;
	m_size.y = height;
}

void Sudoku::draw(sf::RenderWindow* target)
{
}

void Sudoku::t_testSprite(sf::RenderWindow* target, int num)
{
	if (num < m_numberSprites.size())
	{
		sf::Sprite sprite(m_numberSpritesTextures[num]);
		sprite.setPosition(0.0f, 0.0f);
		target->draw(m_numberSprites[num]);
	}
	else
	{
		printf("Error in t_testSprite index out of range\n");
	}
}

void Sudoku::m_generateNumberSprites()
{
	float ratioX = static_cast<unsigned int>(m_size.x / 9.0);
	float ratioY = static_cast<unsigned int>(m_size.y / 9.0);

	std::string chars(" 123456789");

	sf::RenderTexture rt;
	rt.create(ratioX, ratioY);

	sf::Font font;
	if (!font.loadFromFile("lucida-console.ttf"))
	{
		printf("Failed to load font\n");
		getchar();
		exit(-1);
	}

	sf::Text txt;
	txt.setFont(font);

	for (int i = 0; i < 10; i++)
	{
		rt.clear();

		txt.setString(chars[i]);

		// Center the text in the texture before drawing
		sf::FloatRect rect = txt.getLocalBounds();
		txt.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
		txt.setPosition(sf::Vector2f(ratioX / 2.0f, ratioY / 2.0f));

		rt.draw(txt);

		m_numberSpritesImages.push_back(rt.getTexture().copyToImage());
		m_numberSpritesTextures.emplace_back();
		m_numberSpritesImages[i].flipVertically();
		m_numberSpritesTextures[i].create(ratioX, ratioY);
		m_numberSpritesTextures[i].update(m_numberSpritesImages[i].getPixelsPtr(), ratioX, ratioY, 0, 0);
		m_numberSprites.push_back(sf::Sprite(m_numberSpritesTextures[i]));
		//m_numberSprites[i].setTexture(m_numberSpritesTextures[i]);
	}
	// Needs to be out of the loop for some weird reason... tried a bunch of things but if you put
	// m_numberSprites[i].setTexture(m_numberSpritesTextures[i]); inside the loop it doesn't work...
	// since this is not a production code I don't really care to fix it like that
	for(int i = 0; i < 10; i++)
		m_numberSprites[i].setTexture(m_numberSpritesTextures[i]);

	//TODO : Remove return
	return;
}
