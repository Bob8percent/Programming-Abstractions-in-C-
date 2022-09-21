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

void drawSierpinskiTriangle(sf::RenderWindow& window, sf::Vector2f basePos, double size, int order);
void drawInsideTriangles(sf::RenderWindow& window, sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, int order);

int main()
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Sierpinski Triangle");
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

		//	Sierpinski Triangle
		drawSierpinskiTriangle(window, sf::Vector2f(400, 500), 400, 5);

		window.display();
	}
}

void drawSierpinskiTriangle(sf::RenderWindow& window, sf::Vector2f basePos, double size, int order)
{
	//	order0の三角形を描く
	double halfSize = size * 0.5;
	sf::Vector2f A(basePos + sf::Vector2f(0, -halfSize * std::sqrt(3)));
	sf::Vector2f B(basePos + sf::Vector2f(-halfSize, 0));
	sf::Vector2f C(basePos + sf::Vector2f(halfSize, 0));
	drawLine(window, A, B);
	drawLine(window, B, C);
	drawLine(window, C, A);

	drawInsideTriangles(window, A, B, C, order);
}

//	三角形ABCの中に三角形を描く
void drawInsideTriangles(sf::RenderWindow& window, sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, int order)
{
	if (order <= 0)return;

	sf::Vector2f P((A + B) * 0.5f);
	sf::Vector2f Q((B + C) * 0.5f);
	sf::Vector2f R((C + A) * 0.5f);
	drawLine(window, P, Q);
	drawLine(window, Q, R);
	drawLine(window, R, P);
	drawInsideTriangles(window, A, P, R, order - 1);
	drawInsideTriangles(window, P, B, Q, order - 1);
	drawInsideTriangles(window, R, Q, C, order - 1);
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
