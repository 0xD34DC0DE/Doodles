#pragma once
#include <SFML/Graphics.hpp>

#include <vector>;

class Sudoku
{
public:
	Sudoku(float x, float y, float width, float height);

	void fill();
	void setPos(float x, float y);
	void setSize(float width, float height);
	void draw(sf::RenderWindow* target);

	void t_testSprite(sf::RenderWindow* target, int num);
private:
	std::vector<std::vector<int>> m_grid;
	std::vector<std::vector<int>> m_rowPool;
	std::vector<std::vector<int>> m_colPool;
	std::vector<std::vector<int>> m_sqrPool;
	std::vector<sf::Sprite>  m_numberSprites;
	std::vector<sf::Image>   m_numberSpritesImages;
	std::vector<sf::Texture> m_numberSpritesTextures;

	sf::Vector2f m_size;
	sf::Vector2f m_pos;

	void m_generateNumberSprites();

};

