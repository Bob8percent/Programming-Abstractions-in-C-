#include "_Shape.h"

/*
* =================================================================================================
* Shapeクラス
* =================================================================================================
*/
Shape::Shape() {
	setColor("Black");
}

void Shape::setLocation(double x, double y) {
	this->x = x;
	this->y = y;
}

void Shape::move(double dx, double dy) {
	x += dx;
	y += dy;
}

void Shape::setColor(const std::string& color) {
	this->color = color;
}


/*
* =================================================================================================
* Lineクラス
* =================================================================================================
*/
Line::Line(double x1, double y1, double x2, double y2) {
	setLocation(x1, y1);
	this->dx = x2 - x1;
	this->dy = y2 - y1;
}

void Line::draw(sf::RenderWindow& window) {
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(x, y)),
		sf::Vertex(sf::Vector2f(x + dx, y + dy))
	};

	window.draw(line, 2, sf::Lines);
}


/*
* =================================================================================================
* Rectクラス
* =================================================================================================
*/
Rect::Rect(double x, double y, double width, double height) {
	setLocation(x, y);
	this->width = width;
	this->height = height;
}

void Rect::draw(sf::RenderWindow& window) {
	sf::RectangleShape rectangle(sf::Vector2f(width, height));
	rectangle.setPosition(x, y);
	rectangle.setFillColor(sf::Color::Green);
	
	window.draw(rectangle);
}
