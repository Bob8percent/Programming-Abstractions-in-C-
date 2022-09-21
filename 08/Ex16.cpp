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
void drawHFractal(sf::RenderWindow& window, double size, sf::Vector2f centerPos, int order);

int main()
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "H-Fractal");
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

		//	H-Fractal
		drawHFractal(window, 200, sf::Vector2f(400, 300), 4);

		window.display();
	}
}

void drawHFractal(sf::RenderWindow& window, double size, sf::Vector2f centerPos, int order)
{
	if (order < 0)return;

	//	Hを描く : A,B,C,DはHの縦線の端点、M,NはHの横線の端点
	double halfSize = size * 0.5;
	sf::Vector2f A(centerPos.x - halfSize, centerPos.y - halfSize);
	sf::Vector2f B(centerPos.x - halfSize, centerPos.y + halfSize);
	sf::Vector2f C(centerPos.x + halfSize, centerPos.y - halfSize);
	sf::Vector2f D(centerPos.x + halfSize, centerPos.y + halfSize);
	sf::Vector2f M(centerPos.x - halfSize, centerPos.y);
	sf::Vector2f N(centerPos.x + halfSize, centerPos.y);
	drawLine(window, A, B);
	drawLine(window, C, D);
	drawLine(window, M, N);

	drawHFractal(window, size * 0.5, A, order - 1);
	drawHFractal(window, size * 0.5, B, order - 1);
	drawHFractal(window, size * 0.5, C, order - 1);
	drawHFractal(window, size * 0.5, D, order - 1);
}

void drawLine(sf::RenderWindow& window, const sf::Vector2f& A, const sf::Vector2f& B)
{
	sf::Vertex lineCoords[] = {
		sf::Vertex(A),
		sf::Vertex(B)
	};
	window.draw(lineCoords, 2, sf::Lines);
}
