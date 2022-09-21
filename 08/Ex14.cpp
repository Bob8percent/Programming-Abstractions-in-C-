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
void drawTickMarks(sf::RenderWindow& window, const double standardLength, int order, const double halfTickLength = 50);
void drawHalftickMarks(sf::RenderWindow& window, double currentTick, const sf::Vector2f& A, const sf::Vector2f& B, int order);

int main()
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Tick Marks");
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

		//	Tick Marks
		drawTickMarks(window, 200, 6, 50);

		window.display();
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

void drawTickMarks(sf::RenderWindow& window, const double standardLength, int order, const double halfTickLength)
{
	//	基準線(線分AB)を引く
	sf::Vector2f A(400 - standardLength * 0.5, 300);
	sf::Vector2f B(400 + standardLength * 0.5, 300);
	drawLine(window, A, B);

	//	目盛りを引く
	drawHalftickMarks(window, halfTickLength, A, B, order);
}

void drawHalftickMarks(sf::RenderWindow& window, double currentTick, const sf::Vector2f& A, const sf::Vector2f& B, int order)
{
	if (order <= 0)return;

	//	Nから線分ABに下した垂線NM(Mは中点)
	sf::Vector2f M((A + B) * 0.5f);
	sf::Vector2f N(M.x, M.y - currentTick);
	drawLine(window, M, N);
	drawHalftickMarks(window, currentTick * 0.5, A, M, order - 1);
	drawHalftickMarks(window, currentTick * 0.5, M, B, order - 1);
}


