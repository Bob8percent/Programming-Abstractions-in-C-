#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "_Shape.h"
#include "Library/vector.h"

void drawTest(sf::RenderWindow& window) {
    Rect* rp = new Rect(200, 150, 400, 300);
    Vector<Shape*> shapes;
    shapes.add(rp);
    shapes.add(new Line(0, 300, 400, 0));
    shapes.add(new Line(400, 0, 800, 300));
    shapes.add(new Line(800, 300, 400, 600));
    shapes.add(new Line(400, 600, 0, 300));

    for (Shape* s : shapes) {
        s->draw(window);
    }

    for (Shape* s : shapes) {
        delete s;
    }
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

        // なんでも描画
        drawTest(window);

        // 1フレーム終了
        window.display();
    }
}
