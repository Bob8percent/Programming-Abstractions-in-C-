#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "GraphTypes.h"

void initAirlineGraph(SimpleGraph& airline);
void addFlight(SimpleGraph& airline, const std::string& c1, const std::string& c2, int miles);

void printAdjacencyLists(SimpleGraph& g);
void addNode(SimpleGraph& g, const std::string& name);
void addArc(SimpleGraph& g, Node* n1, Node* n2, double cost);

int main() {
	SimpleGraph airline;
	initAirlineGraph(airline);
	printAdjacencyLists(airline);
}

void initAirlineGraph(SimpleGraph& airline) {
	addNode(airline, "Atlanta");
	addNode(airline, "Boston");
	addNode(airline, "Chicago");
	addNode(airline, "Dallas");
	addNode(airline, "Denver");
	addNode(airline, "Los Angeles");
	addNode(airline, "New York");
	addNode(airline, "Portland");
	addNode(airline, "San Francisco");
	addNode(airline, "Seattle");

	addFlight(airline, "Atlanta", "Chicago", 599);
	addFlight(airline, "Atlanta", "Dallas", 725);
	addFlight(airline, "Atlanta", "New York", 756);
	addFlight(airline, "Boston", "New York", 191);
	addFlight(airline, "Boston", "Seattle", 2489);
	addFlight(airline, "Chicago", "Atlanta", 599);
	addFlight(airline, "Chicago", "Denver", 907);
	addFlight(airline, "Dallas", "Atlanta", 725);
	addFlight(airline, "Dallas", "Denver", 650);
	addFlight(airline, "Dallas", "Los Angeles", 1240);
	addFlight(airline, "Dallas", "San Francisco", 1240);
	addFlight(airline, "Denver", "Chicago", 907);
	addFlight(airline, "Denver", "Dallas", 650);
	addFlight(airline, "Denver", "San Francisco", 954);
	addFlight(airline, "Los Angeles", "Dallas", 1240);
	addFlight(airline, "New York", "Atlanta", 756);
	addFlight(airline, "New York", "Boston", 191);
	addFlight(airline, "Portland", "San Francisco", 550);
	addFlight(airline, "Portland", "Seattle", 130);
	addFlight(airline, "San Francisco", "Dallas", 1468);
	addFlight(airline, "San Francisco", "Denver", 954);
	addFlight(airline, "San Francisco", "Portland", 550);
	addFlight(airline, "Seattle", "Boston", 2489);
	addFlight(airline, "Seattle", "Portland", 130);
}

void addFlight(SimpleGraph& airline, const std::string& c1, const std::string& c2, int miles) {
	Node* n1 = airline.nodeMap.at(c1);
	Node* n2 = airline.nodeMap.at(c2);

	addArc(airline, n1, n2, miles);
}

void printAdjacencyLists(SimpleGraph& g) {
	for (std::pair<std::string, Node*> p : g.nodeMap) {//	g->nodesを使うとアドレス順になってしまう(要求順により大きいアドレスへヒープメモリを割り当てるとは限らない)
		std::cout << p.first << " -> ";

		Node* n = p.second;
		bool first = true;
		for (Arc* a : n->arcs) {
			if(!first)std::cout << ", ";
			std::cout << a->end->name;
			first = false;
		}
		std::cout << std::endl;
	}
}

void addNode(SimpleGraph& g, const std::string& name) {
	Node* newNode = new Node;
	newNode->name = name;
	g.nodes.insert(newNode);
	g.nodeMap.insert(std::pair(name, newNode));
}

void addArc(SimpleGraph& g, Node* n1, Node* n2, double cost) {
	Arc* newArc = new Arc;
	newArc->start = n1;
	newArc->end = n2;
	newArc->cost = cost;

	g.arcs.insert(newArc);
	n1->arcs.insert(newArc);
}
