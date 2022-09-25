#include "Maze.h"
#include <fstream>

Maze::Maze(const std::string& filename)
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Maze");

	std::ifstream ifs;
	ifs.open(filename);
	if (ifs.fail())
	{
		std::cerr << "ERROR : Maze::Maze(const std::string& filename)"
			<< " : ファイルを開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::string line;
	rows = 0;
	cols = 0;
	while (std::getline(ifs, line))
	{
		++rows;
		std::size_t l = line.length();
		cols = (cols < l) ? l : cols;
		
		for (std::size_t i = 0; i < l; ++i)
		{
			Square s;
			s.marked = false;
			s.wall = false;

			switch (line.at(i))
			{
			case ' ':
				break;
			case 'S':
			case 's':
				startSquare.x = i;
				startSquare.y = rows - 1;
				break;
			case '+':
				s.wall = true;
				break;
			default:
				break;
			}
			
			maze += s;
		}
	}
}

bool Maze::isOutside(IPoint pt)
{
	return (pt.x < 0) || (cols <= pt.x) || (pt.y < 0) || (rows <= pt.y);
}

bool Maze::wallExists(IPoint pt)
{
	if (isOutside(pt))return false;
	return maze[pt.x + pt.y * cols].wall;
}

void Maze::markSquare(IPoint pt)
{
	maze[pt.x + pt.y * cols].marked = true;
}

void Maze::unmarkSquare(IPoint pt)
{
	maze[pt.x + pt.y * cols].marked = false;
}

void Maze::unmarkSquareAll()
{
	for (int i = 0; i < maze.size(); ++i)maze[i].marked = false;
}

bool Maze::isMarked(IPoint pt)
{
	return maze[pt.x + pt.y * cols].marked;
}

void Maze::drawMaze()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}

		window->clear(sf::Color::Black);

		//	draw maze
		int scale = 20;
		for (int y = 0; y < rows; ++y)
		{
			for (int x = 0; x < cols; ++x)
			{
				sf::RectangleShape rect(sf::Vector2f(scale, scale));

				rect.setPosition(scale * x, scale * y);
				int currentPos = x + y * cols;

				sf::Color color = sf::Color::White;
				if (maze[currentPos].marked)color = sf::Color::Green;
				else if (maze[currentPos].wall)color = sf::Color::Red;

				if ((x == startSquare.x) && (y == startSquare.y))color = sf::Color::Blue;

				rect.setFillColor(color);
				rect.setOutlineThickness(1);
				rect.setOutlineColor(sf::Color::White);
				window->draw(rect);
			}
		}

		window->display();
	}
}

IPoint Maze::adjacentIPoint(IPoint pt, Direction dir)
{
	IPoint dest = pt;
	if (dir == WEST)		dest.x = pt.x - 1;
	else if (dir == EAST)	dest.x = pt.x + 1;
	else if (dir == SOUTH)	dest.y = pt.y - 1;
	else if (dir == NORTH)	dest.y = pt.y + 1;
	return dest;
}

bool Maze::solveMaze()
{
	return solveMaze(startSquare);
}

bool Maze::solveMaze(IPoint pos)
{
	if (isOutside(pos))return true;
	if (wallExists(pos) || isMarked(pos)) return false;

	markSquare(pos);
	for (Direction dir = NORTH; dir <= WEST; dir++)
	{
		IPoint nextPos = adjacentIPoint(pos, dir);
		if (solveMaze(nextPos))
		{
			return true;
		}
	}

	//	現地点からの4方向すべてfalseのときunmarkしてひとつ前の手に戻る
	unmarkSquare(pos);
	return false;
}

int Maze::shortPathLength()
{
	Set<int> counts;
	shortPathLength(startSquare, 0, counts);

	if (!counts.isEmpty())return counts.first();
	return -1;
}

bool Maze::shortPathLength(IPoint pos, int count, Set<int>& counts)
{
	if (isOutside(pos))
	{
		counts += count;
		return true;
	}
	if (wallExists(pos) || isMarked(pos))return false;

	markSquare(pos);

	for (Direction dir = NORTH; dir <= WEST; dir++)
	{
		IPoint nextPos = adjacentIPoint(pos, dir);
		shortPathLength(nextPos, count + 1, counts);
	}
	unmarkSquare(pos);
}
