#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Library/vector.h"
#include "_Shape.h"

void drawTest(sf::RenderWindow& window) {
    Rect r1(50, 30, 10, 20);
    r1.setFillColor(sf::Color::Green);
    Rect r2(100, 30, 40, 20);
    r2.setFillColor(sf::Color::Red);
    Rect r3(200, 200, 50, 60);
    r3.setFillColor(sf::Color::White);

    Oval o1(100, 100, 50, 70);
    window.draw(o1);

    Square s1(200, 200, 100);
    window.draw(s1);

    Circle c1(150, 300, 100);
    window.draw(c1);

    window.draw(r1);
    window.draw(r2);
    window.draw(r3);
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

