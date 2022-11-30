#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Shape
{
public:
	void setLocation(double x, double y);
	void move(double dx, double dy);
	void setColor(const std::string& color);
	virtual void draw(sf::RenderWindow& window) = 0;

//	サブクラスはアクセスできるが、クライアントはアクセスできない
protected:
	//	クライアントに宣言を禁止させる(スライスの防止)
	Shape();
	std::string color;
	double x, y;
};

class Line :public Shape {
public:
	Line(double x1, double y1, double x2, double y2);	//	指定がない限り、スーパークラスのデフォルトコンストラクタが呼ばれる
	virtual void draw(sf::RenderWindow& window);

private:
	double dx;
	double dy;
};

class Rect :public Shape {
public:
	Rect(double x, double y, double width, double height);
	virtual void draw(sf::RenderWindow& window);

private:
	double width;
	double height;
};


