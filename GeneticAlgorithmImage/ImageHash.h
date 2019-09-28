#pragma once
#include <SFML/Graphics.hpp>

struct RGBHash
{
	RGBHash() : rHash(0), gHash(0), bHash(0) {};
	RGBHash(uint64_t rH, uint64_t gH, uint64_t bH) : rHash(rH), gHash(gH), bHash(bH) {};
	uint64_t rHash;
	uint64_t gHash;
	uint64_t bHash;
};

class ImageHash
{
public:
	ImageHash();

	int distance(RGBHash referencHash, RGBHash targetHash);
	RGBHash getRGBHash(const sf::Texture& texture);
private:
	sf::RenderTexture m_scaledTexture;
	sf::Image m_scaledImage;
	uint64_t m_hammingDistance(uint64_t a, uint64_t b);

};

