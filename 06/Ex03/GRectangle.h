#pragma once
#include <string>

class GRectangle
{
public:
	GRectangle();
	GRectangle(double x, double y, double width, double height);

	bool contains(double x, double y) const;
	
	double getX() const;
	double getY() const;
	double getWidth() const;
	double getHeight() const;

	std::string toString() const;

private:
	double mX, mY;
	double mWidth, mHeight;
};

