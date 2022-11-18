#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "graphpriv.h"

int main() {
	Graph<City, Flight> g;
	g.addNode("Atlanta");
	g.addNode("Boston");
	g.addNode("Chicago");
	g.addNode("Dallas");
	g.addNode("Denver");
	g.addNode("Los Angeles");
	g.addNode("New York");
	g.addNode("Portland");
	g.addNode("San Francisco");
	g.addNode("Seattle");

	g.addArc("Atlanta", "Chicago");
	g.addArc("Atlanta", "Dallas");
	g.addArc("Atlanta", "New York");
	g.addArc("Boston", "New York");
	g.addArc("Boston", "Seattle");
	g.addArc("Chicago", "Atlanta");
	g.addArc("Chicago", "Denver");
	g.addArc("Dallas", "Atlanta");
	g.addArc("Dallas", "Denver");
	g.addArc("Dallas", "Los Angeles");
	g.addArc("Dallas", "San Francisco");
	g.addArc("Denver", "Chicago");
	g.addArc("Denver", "Dallas");
	g.addArc("Denver", "San Francisco");
	g.addArc("Los Angeles", "Dallas");
	g.addArc("New York", "Atlanta");
	g.addArc("New York", "Boston");
	g.addArc("Portland", "San Francisco");
	g.addArc("Portland", "Seattle");
	g.addArc("San Francisco", "Dallas");
	g.addArc("San Francisco", "Denver");
	g.addArc("San Francisco", "Portland");
	g.addArc("Seattle", "Boston");
	g.addArc("Seattle", "Portland");

	g.debug();
}
