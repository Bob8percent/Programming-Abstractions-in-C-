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

/*
* KochFractalを描画するプログラム。
* 再帰の強みを生かす実装法ができなかった。反復法と変わらない方法で実装してしまった。
* drawPolarLine(point, r, theta)というpointを始点としてthetaの方向にrだけ描画する、そして返り値は終点の座標。
* これを使って3線分ごとに再帰を使用する方法がある(教科書参照)
*/
void drawLines(sf::RenderWindow& window, const Vector<sf::Vector2f>& vertexCoords);
void kochFractal(sf::RenderWindow& window, int order);
void drawKochFractal(sf::RenderWindow& window, int order, const Vector<sf::Vector2f>& vertexCoords);

int main()
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Koch Fractal");
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

		//	Koch Fractal
		kochFractal(window, 3);

		window.display();
	}
}

void drawLines(sf::RenderWindow& window, const Vector<sf::Vector2f>& vertexCoords)
{
	for (int i = 0; i < vertexCoords.size(); ++i)
	{
		int idx1 = i;
		int idx2 = (i + 1) % vertexCoords.size();
		sf::Vertex lineCoords[] = {
			sf::Vertex(vertexCoords[idx1]),
			sf::Vertex(vertexCoords[idx2])
		};
		window.draw(lineCoords, 2, sf::Lines);
	}
}

void kochFractal(sf::RenderWindow& window, int order)
{
	Vector<sf::Vector2f> vertexCoords;
	double root3 = std::sqrt(3);
	vertexCoords += sf::Vector2f(400, 300-400 / root3),
					sf::Vector2f(200, 300+200 / root3),
					sf::Vector2f(600, 300+200 / root3);
	drawKochFractal(window, order, vertexCoords);
}

void drawKochFractal(sf::RenderWindow& window, int order, const Vector<sf::Vector2f>& vertexCoords)
{
	if (order < 0)
	{
		std::cerr << "ERROR : void drawKochFractal(sf::RenderWindow& window, int order, const Vector<sf::Vector2f>& vertexCoords) : "
			<< "orderが負になっています" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	if (order == 0)
	{
		drawLines(window, vertexCoords);
		return;
	}
	else
	{
		Vector<sf::Vector2f> newCoords;
		for (int i = 0; i < vertexCoords.size(); ++i)
		{
			//	A, Bは線分の端点
			sf::Vector2f A, B;
			A = vertexCoords[i];
			B = vertexCoords[(i + 1) % vertexCoords.size()];
			//	M, Nは3等分された線分上の点, Hは線分上から突き出た点
			sf::Vector2f M, N, H;
			sf::Vector2f direction = (B - A) / 3.0f;
			M = A + direction;
			N = A + direction * 2.0f;
			float angle = M_PI / 3.0f;
			H = M + sf::Vector2f(direction.x * std::cosf(angle) - direction.y * std::sinf(angle),
				direction.x * std::sinf(angle) + direction.y * std::cosf(angle));	//	回転
			newCoords += A, M, H, N;

			if (i == vertexCoords.size() - 1)newCoords += B;
		}

		drawKochFractal(window, order - 1, newCoords);
	}
}



