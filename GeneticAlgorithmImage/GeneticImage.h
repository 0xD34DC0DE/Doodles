#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "ImageHash.h"

struct GeneUnit
{
	GeneUnit(sf::Vector2f _coord, sf::Color _color) : coord(_coord), color(_color) {};
	sf::Vector2f coord;
	sf::Color color;
};

class GeneticImage
{
public:
	GeneticImage(int initialTriplets, const sf::Image& reference, unsigned int maxGeneTriplet = 100);
	GeneticImage(const GeneticImage& genImg);
	GeneticImage& operator=(const GeneticImage& genImg);;
	~GeneticImage();
	GeneticImage copy();
	GeneticImage getMutadedCopy(float percentage, int maxMutation = -1); // maxMutation set to -1 is no maximum
	float difference(const sf::Texture& targetImg);

	const sf::Texture& getTexture();
	void render();

	const int getMaxTriplet() const;
	const sf::Image& getImageRef() const;
	const std::vector<GeneUnit>& getGenes() const;

private:
	sf::RenderTexture m_renderTexture;
	std::vector<GeneUnit> m_genes;
	sf::Vector2u m_imgSize;

	ImageHash m_imgHash;
	RGBHash m_referenceHash;
	unsigned int m_maxGeneTriplet;

	const sf::Image& m_refImage;
	int m_intialTriplet;

	static const std::random_device m_rd;
	static std::mt19937 m_rnd;

	GeneticImage(const std::vector<GeneUnit>& genome, const sf::Image& reference, int maxGeneTriplet);



private:
	sf::Color m_randColor();
	sf::Vector2f m_randCoord();
	GeneUnit m_randGeneUnit();

	std::vector<GeneUnit> m_getMutatedGene(float percentage, int maxMutation);
};

