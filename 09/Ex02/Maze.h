/*
 * File: maze.h
 * ------------
 * This interface exports the Maze class.
 */

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Library/direction.h"
#include "Library/vector.h"
#include "Library/set.h"

 /*
  *       +++++++++++
  *       +     +    
  *       + +++ + +++
  *       +S  +     +
  *       +++++++++++
  */
struct IPoint
{
    int x, y;
};

class Maze
{

public:
    Maze(const std::string& filename);

    bool isOutside(IPoint pt);
    bool wallExists(IPoint pt);
    void markSquare(IPoint pt);
    void unmarkSquare(IPoint pt);
    void unmarkSquareAll();
    bool isMarked(IPoint pt);
    void drawMaze();
    IPoint adjacentIPoint(IPoint start, Direction dir);

    bool solveMaze();
    int shortPathLength();

private:
    struct Square
    {
        bool marked;
        bool wall;
    };
    Vector<Square> maze;
    IPoint startSquare;
    sf::RenderWindow* window;
    int rows;
    int cols;

    bool solveMaze(IPoint pos, int& count);
    bool shortPathLength(IPoint pos, int count, Set<int>& counts);
};
