#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Library/vector.h"
#include "_Shape.h"

class ShapeList :public Vector<Shape*>
{
public:
	void moveToFront(Shape* sp) {
		int idx = find(sp);
		if (idx == -1) {
			std::cerr << "ERROR : void moveToFront(Shape* sp) : "
				<< "spが見つかりません" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		this->remove(idx);
		this->add(sp);
	}

	void moveToBack(Shape* sp) {
		int idx = find(sp);
		if (idx == -1) {
			std::cerr << "ERROR : void moveToBack(Shape* sp) : "
				<< "spが見つかりません" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		this->remove(idx);
		this->insert(0, sp);
	}

	void moveForward(Shape* sp) {
		int idx = find(sp);
		if (idx == -1) {
			std::cerr << "ERROR : void moveForward(Shape* sp) : "
				<< "spが見つかりません" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		if (idx < this->size() - 1) {
			(*this)[idx] = (*this)[idx + 1];
			(*this)[idx + 1] = sp;
		}
	}

	void moveBackward(Shape* sp) {
		int idx = find(sp);
		if (idx == -1) {
			std::cerr << "ERROR : void moveBackward(Shape* sp) : "
				<< "spが見つかりません" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		if (idx > 0) {
			(*this)[idx] = (*this)[idx - 1];
			(*this)[idx - 1] = sp;
		}
	}

	
	void draw(sf::RenderWindow& window) {
		for (Shape* sp : (*this)) {
			window.draw(*sp);
		}
	}

	void free() {
		for (int i = 0; i < this->size(); ++i) {
			delete (*this)[i];
		}
	}

	Shape* getShapeAt(float x, float y) {
		for (Shape* sp : (*this)) {
			if (sp->contains(x, y))return sp;
		}
		return  nullptr;
	}

private:
	int find(Shape* sp) {
		for (int i = 0; i < this->size(); ++i) {
			if (sp == (*this)[i])return i;
		}

		return -1;
	}
};

