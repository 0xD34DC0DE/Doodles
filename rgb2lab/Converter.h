#pragma once
#include <SFML/Graphics.hpp>

class Converter
{
public:
	Converter();

	static void sRGB2LinearRGB(sf::Image* imagePtr);
	static void sRGB2LinearRGB(sf::Image* imagePtr);
private:

	static void inline m_sRGB2linRGB(uint32_t srgb);
	static void inline m_linRGB2XYZ(uint32_t linRGB);
	static void inline m_XYZ2linRGB(uint32_t xyz);
	static void inline m_XYZ2LAB(uint32_t xyz);
};

