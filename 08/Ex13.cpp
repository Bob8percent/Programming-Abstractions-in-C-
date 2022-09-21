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

void subdivideCanvas(sf::RenderWindow& window, double x, double y, double width, double height);
void drawLine(sf::RenderWindow& window, const sf::Vector2f& A, const sf::Vector2f& B);
void drawRect(sf::RenderWindow& window, double x, double y, double width, double height);

int main()
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Mondrian");
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

		//	draw
		setRandomSeed(1);
		subdivideCanvas(window, 0, 0, 800, 600);

		window.display();
	}
}

void subdivideCanvas(sf::RenderWindow& window, double x, double y, double width, double height)
{
	const double MIN_AREA = 10000;
	const double MIN_EDGE = 100;

	if (width * height > MIN_AREA && width > MIN_EDGE && height > MIN_EDGE)
	{
		drawRect(window, x, y, width, height);

		if (width > height)
		{
			//	縦に切る
			double mid = randomReal(width * 0.4, width * 0.6);
			//drawLine(window, sf::Vector2f(x + mid, y), sf::Vector2f(x + mid, y + height));
			subdivideCanvas(window, x, y, mid, height);
			subdivideCanvas(window, x + mid, y, width - mid, height);
		}
		else
		{
			//	横に切る
			double mid = randomReal(width * 0.4, width * 0.6);
			//drawLine(window, sf::Vector2f(x, y + mid), sf::Vector2f(x + width, y + mid));
			subdivideCanvas(window, x, y, width, mid);
			subdivideCanvas(window, x, y + mid, width, height - mid);
		}
	}
}

void drawLine(sf::RenderWindow& window, const sf::Vector2f& A, const sf::Vector2f& B)
{
	sf::Vertex lineCoords[] = {
		sf::Vertex(A),
		sf::Vertex(B)
	};
	window.draw(lineCoords, 2, sf::Lines);
}

void drawRect(sf::RenderWindow& window, double x, double y, double width, double height)
{
	sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setPosition(x, y);
	sf::Color defCol(255, 255, 255);
	sf::Color rndCol((int)(255 * randomReal(0, 1)), (int)(255 * randomReal(0, 1)), (int)(255 * randomReal(0, 1)));
	rect.setFillColor(defCol * rndCol);
	rect.setOutlineThickness(10);
	rect.setOutlineColor(sf::Color::Black);

	window.draw(rect);
}

