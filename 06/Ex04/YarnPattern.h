#pragma once
#include "Library/vector.h"
#include "Library/gtypes.h"
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class YarnPattern
{
public:
	YarnPattern();
	YarnPattern(int nAcross, int nDown, int delta);

	void draw() const;

private:
	int mDelta;
	Vector<GPoint> coords;
	sf::RenderWindow* window;

	void initSFMLWindow();
	void initCoords(int nAcross, int nDown);
	void drawLines() const;
};

