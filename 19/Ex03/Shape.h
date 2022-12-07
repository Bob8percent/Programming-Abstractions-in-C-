#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Shape :public sf::Shape {
public:
    virtual bool contains(float x, float y) = 0;
};

class Rect :public Shape {
public:
    Rect(float x, float y, float width, float height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;

        update();
    }

    //  頂点の数を取得
    virtual std::size_t getPointCount() const
    {
        return 4;
    }

    //  頂点を取得
    virtual sf::Vector2f getPoint(std::size_t index) const
    {
        if (index == 0)return sf::Vector2f(x, y);
        if (index == 1)return sf::Vector2f(x + width, y);
        if (index == 2)return sf::Vector2f(x + width, y + height);
        if (index == 3)return sf::Vector2f(x, y + height);
    }

    virtual bool contains(float x, float y) {
        return (this->x < x) && x < (this->x + width)
            && (this->y < y) && y < (this->y + height);
    }

private:
    float x, y, width, height;
};

class Oval :public Shape {
public:
    Oval(float x, float y, float rx, float ry){
        this->x = x;
        this->y = y;
        this->rx = rx;
        this->ry = ry;
        update();
    }

    virtual std::size_t getPointCount() const
    {
        return 30;
    }

    virtual sf::Vector2f getPoint(std::size_t index) const
    {
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * rx;
        float y = std::sin(angle) * ry;

        return sf::Vector2f(x + this->x, y + this->y);
    }

    virtual bool contains(float x, float y) {
        x = x - this->x;
        y = (rx / ry) * (y - this->y);

        return x * x + y * y < rx* rx;
    }

private:
    float x, y, rx, ry;
};

class Circle :public Oval {
public:
    Circle(float x, float y, float r) :Oval(x, y, r, r) {}
};

class Square :public Rect {
public:
    Square(float x, float y, float size) :Rect(x, y, size, size) {}
};
