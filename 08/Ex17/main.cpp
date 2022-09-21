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
sf::Vector2f drawPolarLine(sf::RenderWindow& window, const sf::Vector2f& P, double r, double angle);
void drawFractalTree(sf::RenderWindow& window, double size, sf::Vector2f pos, int order);
void drawBranches(sf::RenderWindow& window, double size, sf::Vector2f pos, double angle, int order);

int main()
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Fractal Tree");
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

		//	Fractal Tree
		drawFractalTree(window, 150, sf::Vector2f(400, 600), 7);

		window.display();
	}
}

void drawFractalTree(sf::RenderWindow& window, double size, sf::Vector2f pos, int order)
{
	//	幹
	double angle = -M_PI * 0.5;
	sf::Vector2f Pt = drawPolarLine(window, pos, size, angle);

	//	枝
	drawBranches(window, size, Pt, angle, order);
}

void drawBranches(sf::RenderWindow& window, double size, sf::Vector2f pos, double angle, int order)
{
	if (order == 0)return;

	double theta = angle + M_PI * 0.25;
	double halfSize = size / 1.65;
	sf::Vector2f Pt = drawPolarLine(window, pos, halfSize, theta);
	drawBranches(window, halfSize, Pt, theta, order - 1);
	theta = angle - M_PI * 0.25;
	Pt = drawPolarLine(window, pos, halfSize, theta);
	drawBranches(window, halfSize, Pt, theta, order - 1);
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
