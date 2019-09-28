#include "GeneticImage.h"


#ifdef _DEBUG
std::mt19937 GeneticImage::m_rnd = std::mt19937(0);
#else 
std::mt19937 GeneticImage::m_rnd = std::mt19937(std::random_device{}());
#endif // _DEBUG

GeneticImage::GeneticImage(int initialTriplets, const sf::Image& reference, unsigned int maxGeneTriplet) : m_refImage(reference)
{
	m_intialTriplet = initialTriplets;
	m_maxGeneTriplet = maxGeneTriplet;
	m_imgSize = reference.getSize();
	m_renderTexture.create(m_imgSize.x, m_imgSize.y);

	if (initialTriplets > m_maxGeneTriplet)
		initialTriplets = m_maxGeneTriplet;

	for (int i = 0; i < initialTriplets * 3; i++)
	{
		m_genes.emplace_back(m_randGeneUnit());
	}

	render();
	m_referenceHash = m_imgHash.getRGBHash(m_renderTexture.getTexture());
}

GeneticImage::GeneticImage(const GeneticImage & genImg) : m_refImage(genImg.getImageRef())
{
	m_genes = std::vector<GeneUnit>(genImg.getGenes());
	m_maxGeneTriplet = genImg.getMaxTriplet();
	m_imgSize = m_refImage.getSize();
	m_renderTexture.create(m_imgSize.x, m_imgSize.y);
	render();
	m_referenceHash = m_imgHash.getRGBHash(m_renderTexture.getTexture());
}

GeneticImage & GeneticImage::operator=(const GeneticImage & genImg)
{
	m_refImage = genImg.getImageRef();
	m_genes = std::vector<GeneUnit>(genImg.getGenes());
	m_maxGeneTriplet = genImg.getMaxTriplet();
	m_imgSize = m_refImage.getSize();
	m_renderTexture.create(m_imgSize.x, m_imgSize.y);
	render();
	m_referenceHash = m_imgHash.getRGBHash(m_renderTexture.getTexture());
}

GeneticImage::~GeneticImage()
{
	std::printf("DeleterCalled for %p\n", this);
}

GeneticImage GeneticImage::copy()
{
	return GeneticImage(m_genes, m_refImage, m_maxGeneTriplet);
}

GeneticImage GeneticImage::getMutadedCopy(float percentage, int maxMutation)
{
	return GeneticImage(m_getMutatedGene(percentage, maxMutation), m_refImage, m_maxGeneTriplet);
}

float GeneticImage::difference(const sf::Texture& targetTexture)
{
	return static_cast<float>(std::abs(m_imgHash.distance(m_referenceHash, m_imgHash.getRGBHash(targetTexture))));
}

const sf::Texture& GeneticImage::getTexture()
{
	return m_renderTexture.getTexture();
}

void GeneticImage::render()
{
	//TODO : Instead of creating a VA everytime, keep a VA and modify it just like the genome
	sf::VertexArray VA;
	VA.setPrimitiveType(sf::PrimitiveType::Triangles);

	for (auto& u : m_genes)
	{
		VA.append(sf::Vertex(u.coord, u.color));
	}

	m_renderTexture.clear();
	m_renderTexture.draw(VA);
}

const int GeneticImage::getMaxTriplet() const
{
	return m_maxGeneTriplet;
}

const sf::Image & GeneticImage::getImageRef() const
{
	return m_refImage;
}

const std::vector<GeneUnit>& GeneticImage::getGenes() const
{
	return m_genes;
}

GeneticImage::GeneticImage(const std::vector<GeneUnit>& genome, const sf::Image & reference, int maxGeneTriplet) : m_refImage(reference)
{
	m_genes = std::vector<GeneUnit>(genome);
	m_maxGeneTriplet = maxGeneTriplet;
}

sf::Color GeneticImage::m_randColor()
{
	static std::uniform_int_distribution<unsigned int> rndChar(0x00, 0xFF);

	return sf::Color(rndChar(m_rnd), rndChar(m_rnd), rndChar(m_rnd), rndChar(m_rnd));
}

sf::Vector2f GeneticImage::m_randCoord()
{
	static std::uniform_real_distribution<float> rndX;
	static std::uniform_real_distribution<float> rndY;

	rndX.param(std::uniform_real_distribution<float>::param_type(0.0f, static_cast<float>(m_imgSize.x)));
	rndY.param(std::uniform_real_distribution<float>::param_type(0.0f, static_cast<float>(m_imgSize.y)));

	return sf::Vector2f(rndX(m_rnd), rndY(m_rnd));
}

GeneUnit GeneticImage::m_randGeneUnit()
{
	return GeneUnit(m_randCoord(), m_randColor());
}

std::vector<GeneUnit> GeneticImage::m_getMutatedGene(float percentage, int maxMutation)
{
	int mutations = 0;
	std::vector<GeneUnit> mutated(m_genes);
	std::size_t geneSize = m_genes.size();
	std::uniform_real_distribution<float> randPercent(0.0f, 1.0f);

	for (int i = 0; i < geneSize; i++)
	{
		if (maxMutation > 0 && mutations == maxMutation)
			break;

		if (randPercent(GeneticImage::m_rnd) <= percentage)
		{
			mutated[i] = m_randGeneUnit();
			mutations++;
		}
	}
	return mutated;
}
