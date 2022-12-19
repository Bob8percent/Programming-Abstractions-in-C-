#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>
#include "Plot.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//	ファンクターのためのクラス(x=1=>y=1となるよう調整している)
class Constant {
public:
	float operator()(float x) const{
		return 1;
	}
}; 
class Logarithmic {
public:
	float operator()(float x) const{
		return std::log(x) + 1;
	}
};
class Linear {
public:
	float operator()(float x) const{
		return x;
	}
};
class NlogN {
public:
	float operator()(float x) const{
		return x * std::log(x) + 1;
	}
};
class Quadratic {
public:
	float operator()(float x) const{
		return x * x;
	}
};
class Exponential {
public:
	float operator()(float x) const{
		return std::exp(x - 1);
	}
};

void testDraw(sf::RenderWindow& window) {
	Plot p(SCREEN_WIDTH, SCREEN_HEIGHT, 1, 15);
	p.draw(window, Constant());
	p.draw(window, Logarithmic());
	p.draw(window, Linear());
	p.draw(window, NlogN());
	p.draw(window, Quadratic());
	p.draw(window, Exponential());
}

int main() {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "plot");
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

		testDraw(window);

		window.display();
	}
}
