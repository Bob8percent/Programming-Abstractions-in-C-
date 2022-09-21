#define _USE_MATH_DEFINES

#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

void drawLine(sf::RenderWindow& window, const sf::Vector2f& A, const sf::Vector2f& B);
sf::Vector2f drawPolarLine(sf::RenderWindow& window, const sf::Vector2f& P, double r, double angle);	//	時計回りを正、x軸からのangle
sf::Vector2f drawCoastLine(sf::RenderWindow& window, const sf::Vector2f& P, double r, double angle, int order);

int main()
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Coast Line");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);

		//	Coast Line
		setRandomSeed(1);
		drawCoastLine(window, sf::Vector2f(0, 300), 800, 0, 8);

		window.display();
	}
}

sf::Vector2f drawCoastLine(sf::RenderWindow& window, const sf::Vector2f& P, double r, double angle, int order)
{
	if (order <= 0)
	{
		return drawPolarLine(window, P, r, angle);
	}

	int dimple = randomChance(0.5) ? 1 : -1;

	sf::Vector2f Pt = drawCoastLine(window, P, r / 3, angle, order - 1);
	Pt = drawCoastLine(window, Pt, r / 3, angle + dimple * (M_PI / 3), order - 1);
	Pt = drawCoastLine(window, Pt, r / 3, angle - dimple * (M_PI / 3), order - 1);
	return drawCoastLine(window, Pt, r / 3, angle, order - 1);
}

void drawLine(sf::RenderWindow& window, const sf::Vector2f& A, const sf::Vector2f& B)
{
	sf::Vertex lineCoords[] = {
		sf::Vertex(A),
		sf::Vertex(B)
	};
	window.draw(lineCoords, 2, sf::Lines);
}

sf::Vector2f drawPolarLine(sf::RenderWindow& window, const sf::Vector2f& P, double r, double angle)
{
	sf::Vector2f destination(P + sf::Vector2f(r * std::cosf(angle), r * std::sinf(angle)));
	
	drawLine(window, P, destination);

	return destination;
}


