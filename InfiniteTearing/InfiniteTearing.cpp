#include <sfml/Graphics.hpp>
#include "PerlinNoise.h"

sf::Color noiseColor(double x, double y, siv::PerlinNoise& noiseEngine)
{
	auto r = static_cast<unsigned char>(std::floor(noiseEngine.octaveNoise0_1(x, y + 100.0f, 3) * 255.0f));
	auto g = static_cast<unsigned char>(std::floor(noiseEngine.octaveNoise0_1(x, y + 1000.0f, 3) * 255.0f));
	auto b = static_cast<unsigned char>(std::floor(noiseEngine.octaveNoise0_1(x, y + 10000.0f, 3) * 255.0f));
	return sf::Color(r,g,b);
}

float lerp(float v0, float v1, float t) {
	return (1.0f - t) * v0 + t * v1;
}

float getInverseReciprocal(float a)
{
	return -1.0f / a;
}

void noiseLine(sf::VertexArray& va, sf::Vector2f pt1, sf::Vector2f pt2, unsigned int octaves, float amplitude)
{
	static siv::PerlinNoise pNoise;

	std::size_t vCount = va.getVertexCount();

	float increment = std::abs(pt2.x - pt1.x) / static_cast<float>(vCount);
	float minX = std::min(pt1.x, pt2.x);

	float slope = (pt2.y - pt1.y) / (pt2.x - pt1.x);
	float bias = pt1.y - slope * pt1.x;
	float perpendicularSlope = getInverseReciprocal(slope);
	float perpendicularBias = pt1.y - pt1.x * perpendicularSlope;

	for (unsigned int i = 0; i < vCount; i++)
	{
		va[i].position.x = pNoise.octaveNoise0_1(increment * static_cast<float>(i), octaves);
		float x = static_cast<float>(i) * increment + minX;
		va[i].position.x = 
		va[i].position.y = va[i].position.x * slope + bias;
	}

}

int main()
{
	unsigned int width = 512;
	unsigned int height = 512;

	sf::RenderWindow window(sf::VideoMode(width, height), "Infinite tearing");
	window.setFramerateLimit(60);

	sf::VertexArray VA;
	VA.setPrimitiveType(sf::PrimitiveType::LineStrip);
	siv::PerlinNoise pNoise;

	for (int i = 0; i < width; i++)
	{
		VA.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::White));
	}

	noiseLine(VA, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(width * 0.5f, height * .5f), 0, 1.0f);

	float offset = 0.0f;
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
		window.draw(VA);
		window.display();
		offset += 0.01f;
	}

	return 0;
}