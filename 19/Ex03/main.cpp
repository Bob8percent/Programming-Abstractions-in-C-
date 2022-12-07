#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Library/vector.h"
#include "_Shape.h"

//  線分P1P2と点P0について
//  参照：https://zenn.dev/boiledorange73/articles/0037-js-distance-pt-seg
bool containsLine(sf::Vector2f& P1, sf::Vector2f& P2, float x, float y) {
    float a = P2.x - P1.x;
    float b = P2.y - P1.y;

    //  線分と点との距離
    float t0 = -(a * (P1.x - x) + b * (P1.y - y));
    float r2 = a * a + b * b;
    if (t0 < 0) return ((P1.x - x) * (P1.x - x) + (P1.y - y) * (P1.y - y)) < 0.5f;
    if (t0 > r2)return ((P2.x - x) * (P2.x - x) + (P2.y - y) * (P2.y - y)) < 0.5f;

    float m = a * (P1.y - y) - b * (P1.x - x);
    float d = (m * m) / (a * a + b * b);
    return d < 0.5f;
}

void drawTest(sf::RenderWindow& window) {
    Rect r1(50, 30, 10, 20);
    r1.setFillColor(sf::Color::Green);
    Rect r2(100, 30, 40, 20);
    r2.setFillColor(sf::Color::Red);
    Rect r3(200, 200, 50, 60);
    r3.setFillColor(sf::Color::White);

    Oval o1(100, 100, 50, 70);
    Square s1(200, 200, 100);
    Circle c1(150, 300, 100);

    float x = 101, y = 100;
    Square point(x, y, 10);
    point.setFillColor(sf::Color::Green);

    Vector<sf::Shape*> rv;
    rv += & r1, & r2, & r3, & o1, & s1, & c1, & point;

    //  Shapeクラスを継承しているのでdraw呼び出しできる
    for (sf::Shape* p : rv) {
        window.draw(*p);
    }

    //  線分に関して
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(10, 10)),
        sf::Vertex(sf::Vector2f(150, 150))
    };
    window.draw(line, 2, sf::Lines);
    std::cout<< containsLine(line[0].position, line[1].position, x, y);

}

int main() {
    // ウィンドウ生成
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shape test");

    // ウィンドウが開いている間、プログラムを続ける
    while (window.isOpen())
    {
        // タマってるイベントを全部お世話する。
        sf::Event event;
        while (window.pollEvent(event))
        {
            // 閉じる要求検知。ウィンドウを閉じる。
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // ウィンドウを黒でクリア
        window.clear(sf::Color::Black);

        // 描画処理
        drawTest(window);

        // 1フレーム終了
        window.display();
    }
}

