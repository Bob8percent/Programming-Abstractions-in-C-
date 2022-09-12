#include "YarnPattern.h"

YarnPattern::YarnPattern()
{
	initSFMLWindow();
	initCoords(2, 2);
	mDelta = 1;
}

YarnPattern::YarnPattern(int nAcross, int nDown, int delta)
{
	initSFMLWindow();
	initCoords(nAcross, nDown);
	mDelta = delta;
}

void YarnPattern::draw() const
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}

		window->clear(sf::Color::Black);

		//	描画処理
		drawLines();

		window->display();
	}
}

void YarnPattern::initSFMLWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My Window");
}

void YarnPattern::initCoords(int nAcross, int nDown)
{
	Vector<GPoint> leftPegs, rightPegs;
	double d = SCREEN_HEIGHT / (double)(nDown - 1);
	for (int i = 0; i < nDown; ++i)
	{
		rightPegs.add(GPoint(SCREEN_WIDTH, d * i));
		leftPegs.add(GPoint(0, SCREEN_HEIGHT - d * i));
	}

	Vector<GPoint> upPegs, downPegs;
	d = SCREEN_WIDTH / (double)(nAcross - 1);
	for (int i = 1; i < nAcross-1; ++i)
	{
		upPegs.add(GPoint(d*i,0));
		downPegs.add(GPoint(SCREEN_WIDTH - d * i, SCREEN_HEIGHT));
	}

	coords += upPegs;
	coords += rightPegs;
	coords += downPegs;
	coords += leftPegs;
}


void YarnPattern::drawLines() const
{
	for (int i = 0; i < coords.size(); ++i)
	{
		sf::Vertex lineCoords[] = {
			sf::Vertex(sf::Vector2f(coords[i].x,coords[i].y)),
			sf::Vertex(sf::Vector2f(coords[(i + mDelta) % coords.size()].x,coords[(i + mDelta) % coords.size()].y))
		};
		window->draw(lineCoords, 2, sf::Lines);	
	}
}

