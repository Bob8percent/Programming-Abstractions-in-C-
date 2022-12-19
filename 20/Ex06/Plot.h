#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Plot
{
public:
	Plot(int width, int height, float minX, float maxX, float minY, float maxY) {
		this->width = width;
		this->height = height;
		this->minX = minX;
		this->maxX = maxX;
		this->minY = minY;
		this->maxY = maxY;
	}

	//	ファンクターを使用したplot
	template <typename Functor>
	//	TODO : Functor&だと変換できない場合があるのでtemplateについて要勉強
	void draw(sf::RenderWindow& window, Functor fn) {
		float px0 = 0;
		float py0 = height - height * (fn(minX) - minY) / (maxY - minY);
		for (int i = 1; i <= width; ++i) {
			//	fn上のx,yを求める
			float x = minX + i * (maxX - minX) / width;
			float y = fn(x);
			//	(x,y)をpixelに変換
			float px1 = width * (x - minX) / (maxX - minX);
			float py1 = height - height * (y - minY) / (maxY - minY);
			drawLine(window, px0, py0, px1, py1);

			px0 = px1;
			py0 = py1;
		}
	}

	//	関数ポインタを使用したplot
	void draw(sf::RenderWindow& window, float (*fn)(float)) {
		float px0 = 0;
		float py0 = height - height * (fn(minX) - minY) / (maxY - minY);
		for (int i = 1; i <= width; ++i) {
			//	fn上のx,yを求める
			float x = minX + i * (maxX - minX) / width;
			float y = fn(x);
			//	(x,y)をpixelに変換
			float px1 = width * (x - minX) / (maxX - minX);
			float py1 = height - height * (y - minY) / (maxY - minY);

			drawLine(window, px0, py0, px1, py1);
			px0 = px1;
			py0 = py1;
		}
	}

private:
	float minX, maxX, minY, maxY;
	int width, height;

	void drawLine(sf::RenderWindow& window, float x0, float y0, float x1, float y1) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x0, y0)),
			sf::Vertex(sf::Vector2f(x1, y1))
		};

		window.draw(line, 2, sf::Lines);
	}
};
