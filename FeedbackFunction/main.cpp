#include <string>
#include <random>
#include <SFML/Graphics.hpp>
#include <deque>

#define DIV 1

//TODO : finish implementing average graph
int main()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> normDist; // default range 0.0f to 1.0f
	double init = normDist(mt);
	std::string state = std::to_string(init*1e10).substr(0, 10);


	unsigned int width = 512;
	unsigned int height = 512;

	sf::VertexArray vertexArray;
	sf::VertexArray avgVertArray;
	vertexArray.setPrimitiveType(sf::PrimitiveType::LineStrip);
	avgVertArray.setPrimitiveType(sf::PrimitiveType::LineStrip);
	double ratio = (1.0 / 9999999999.0);

	std::deque<sf::Vector2f> pts;
	float runningAverage = 0.0f;

	//48 57
	for (unsigned int n = 0; n < width / DIV; n++)
	{
		unsigned int sum = state[0] - 48;
		for (unsigned int i = 1; i < 10; i++)
			sum *= (state[i] - 48) + 1;
		std::string appendString = std::to_string(sum);
		state = state.substr(appendString.size(), state.size()) + appendString;
		pts.emplace_back(static_cast<float>(n * DIV), static_cast<float>(ratio * std::atof(state.c_str()) * static_cast<float>(height)));
		runningAverage += pts.back().y;
	}

	for (auto& p : pts)
	{
		vertexArray.append(sf::Vertex(p, sf::Color::Green));
	}

	sf::RenderWindow window(sf::VideoMode(width, height), "Feedback function");
	window.setFramerateLimit(60);

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

		

		for (unsigned int i = 0; i < pts.size() - 1; i++)
		{
			pts[i].x = static_cast<float>(i * DIV);
			pts[i].y = pts[i + 1].y;
		}

		pts.pop_front();

		unsigned int sum = state[0] - 48;
		for (unsigned int i = 1; i < 10; i++)
		{
			unsigned char c = state[i] - 48;
			(c % 2 == 0) ? sum += c : sum *= c;
		}
		std::string appendString = std::to_string(sum);
		state = state.substr(appendString.size(), state.size()) + appendString;
		if (std::atof(state.c_str()) * static_cast<float>(height) > 500)
		{
			volatile int a = 0;
		}
		pts.emplace_back(static_cast<float>(width), static_cast<float>(ratio * std::atof(state.c_str()) * static_cast<float>(height)));

		vertexArray.clear();

		for (unsigned int i = 0; i < pts.size(); i++)
		{
			vertexArray.append(sf::Vertex(pts[i], sf::Color::Green));
		}

		window.clear();
		window.draw(vertexArray);
		window.display();
	}

	return 0;
}