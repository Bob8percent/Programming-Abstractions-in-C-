#include "GRectangle.h"
#include <iostream>
#include <sstream>

GRectangle::GRectangle()
{
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
}

GRectangle::GRectangle(double x, double y, double width, double height)
{
	if (width < 0 || height < 0)
	{
		std::cerr << "ERROR : GRectangle::GRectangle(double x, double y, double width, double height) : "
			<< "widthまたはheightが負になっています" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	mX = x;
	mY = y;
	mWidth = width;
	mHeight = height;
}

bool GRectangle::contains(double x, double y) const
{
	return (mX < x < mX + mWidth) && (mY < y < mY + mHeight);
}

double GRectangle::getX() const
{
	return mX;
}

double GRectangle::getY() const
{
	return mY;
}

double GRectangle::getWidth() const
{
	return mWidth;
}

double GRectangle::getHeight() const
{
	return mHeight;
}

std::string GRectangle::toString() const
{
	std::ostringstream oss;
	oss << "(" << mX << ", " << mY << ", " << mWidth << ", " << mHeight << ")";
	return oss.str();
}
