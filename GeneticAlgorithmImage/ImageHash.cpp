#include "ImageHash.h"

ImageHash::ImageHash()
{
	m_scaledTexture.create(8, 8);
}

int ImageHash::distance(RGBHash referencHash, RGBHash targetHash)
{
	return m_hammingDistance(referencHash.rHash, targetHash.rHash) +
		m_hammingDistance(referencHash.gHash, targetHash.gHash) +
		m_hammingDistance(referencHash.bHash, targetHash.bHash);
}

RGBHash ImageHash::getRGBHash(const sf::Texture& texture)
{
	sf::RectangleShape rect(sf::Vector2f(8.0f, 8.0f));
	rect.setTexture(&texture);

	m_scaledTexture.draw(rect);
	m_scaledImage = m_scaledTexture.getTexture().copyToImage();

	uint8_t rPxls[64], bPxls[64], gPxls[64];

	const uint8_t* pixelPtr = m_scaledImage.getPixelsPtr();

	for (int i = 0; i < 64; i++)
	{
		sf::Color pixel = sf::Color(pixelPtr[i]);
		//BGR
		rPxls[i] = pixelPtr[i * 4 + 2];
		gPxls[i] = pixelPtr[i * 4 + 1];
		bPxls[i] = pixelPtr[i * 4 + 0];
	}
	
	uint32_t sumR = 0, sumG = 0, sumB = 0;

	for (int i = 0; i < 64; i++)
	{
		sumR += rPxls[i];
		sumG += gPxls[i];
		sumB += bPxls[i];
	}

	sumR /= 64;
	sumG /= 64;
	sumB /= 64;

	uint64_t bitsR = 0, bitsG = 0, bitsB = 0;

	for (int i = 0; i < 64; i++)
	{
		if (rPxls[i] > sumR)
			bitsR |= 1 << i;

		if (gPxls[i] > sumG)
			bitsG |= 1 << i;

		if (bPxls[i] > sumB)
			bitsB |= 1 << i;
	}

	return  RGBHash(bitsR, bitsG, bitsB);

}

uint64_t ImageHash::m_hammingDistance(uint64_t a, uint64_t b)
{
	//Wegner's algorithm
	uint64_t dist = 0;

	// Count the number of bits set
	for (uint64_t val = a ^ b; val > 0; val /= 2)
	{
		// If A bit is set, so increment the count
		if (val & 1)
			dist++;
		// Clear (delete) val's lowest-order bit
	}
	// Return the number of differing bits
	return dist;
}
