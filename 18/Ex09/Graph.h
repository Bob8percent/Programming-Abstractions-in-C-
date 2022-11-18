#pragma once
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include "Library/vector.h"
#include "_PQueue.h"

template<typename NodeType, typename ArcType>
class Graph {
public:
	Graph();
	Graph(const Graph<NodeType, ArcType>& src);
	~Graph();

	int size() const;
	bool isEmpty() const;
	void clear();

	void addNode(const std::string& name);
	void addNode(NodeType* node);

	void removeNode(const std::string& name);
	void removeNode(NodeType* node);

	NodeType* getNode(const std::string& name) const;

	void addArc(const std::string& s1, const std::string& s2);
	void addArc(NodeType* n1, NodeType* n2);
	void addArc(ArcType* arc);

	void removeArc(const std::string& s1, const std::string& s2);
	void removeArc(NodeType* n1, NodeType* n2);
	void removeArc(ArcType* arc);

	bool isConnected(const std::string& s1, const std::string& s2) const;
	bool isConnected(NodeType* n1, NodeType* n2) const;

	std::set<NodeType*>& getNodeSet() const;
	std::set<ArcType*>& getArcSet() const;
	std::set<ArcType*>& getArcSet(const std::string& name) const;
	std::set<ArcType*>& getArcSet(NodeType* node) const;

	std::set<NodeType*> getNeighbors(const std::string& name) const;
	std::set<NodeType*> getNeighbors(NodeType* node) const;

	Graph<NodeType, ArcType>& operator=(const Graph<NodeType, ArcType>& src);

	Vector<ArcType*> findShortestPath(const std::string& startName, const std::string& endName);
	Vector<ArcType*> findShortestPath(NodeType* start, NodeType* end);

	void mapDFS(void (*fn)(NodeType*), NodeType* start);
	void mapBFS(void (*fn)(NodeType*), NodeType* start);

	void debug() {
		for (std::pair<std::string, NodeType*> p : nodeMap) {
			std::cout << p.first << " -> ";

			NodeType* n = p.second;
			bool first = true;
			for (ArcType* a : n->arcs) {
				if (!first)std::cout << ", ";
				std::cout << a->end->name;
				first = false;
			}
			std::cout << std::endl;
		}
	}

private:
	std::set<NodeType*> nodes;
	std::set<ArcType*> arcs;
	std::map<std::string, NodeType*> nodeMap;

	void deepCopy(const Graph<NodeType, ArcType>& src);

	double getPathCost(Vector<ArcType*> path) const;
};

template<typename NodeType, typename ArcType>
Graph<NodeType, ArcType>::Graph() {
}

template<typename NodeType, typename ArcType>
Graph<NodeType, ArcType>::Graph(const Graph<NodeType, ArcType>& src) {
	deepCopy(src);
}

template<typename NodeType, typename ArcType>
Graph<NodeType, ArcType>::~Graph() {
	clear();
}

template<typename NodeType, typename ArcType>
int Graph<NodeType, ArcType>::size() const {
	return nodes.size();
}

template<typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isEmpty() const {
	return nodes.empty();
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::clear() {
	for (NodeType* n : nodes) {
		delete n;	//	nullptrは代入しない。set内のtreeを維持するため
	}
	for (ArcType* a : arcs) {
		delete a;
	}

	nodes.clear();
	arcs.clear();
	nodeMap.clear();
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::addNode(const std::string& name) {
	if (nodeMap.contains(name)) {
		std::cerr << "ERROR : void Graph<NodeType, ArcType>::addNode(const std::string& name) : "
			<< "すでにGraph内にnameを名前とするノードが存在します" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	NodeType* newNode = new NodeType;
	newNode->name = name;
	addNode(newNode);
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::addNode(NodeType* node) {
	nodes.insert(node);
	nodeMap.insert(std::pair(node->name, node));
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeNode(const std::string& name) {
	removeNode(nodeMap[name]);
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeNode(NodeType* node) {
	Vector<ArcType*> removeArcs;
	for (ArcType* a : arcs) {
		if (a->start == node || a->end == node) {
			removeArcs += a;
		}
	}
	for (int i = 0; i < removeArcs.size(); ++i) {
		removeArc(removeArcs[i]);
	}

	nodes.erase(node);
	delete node;
	node = nullptr;
}

template<typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::getNode(const std::string& name) const {
	return nodeMap[name];
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::addArc(const std::string& s1, const std::string& s2) {
	addArc(nodeMap[s1], nodeMap[s2]);
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::addArc(NodeType* n1, NodeType* n2) {
	ArcType* newArc = new ArcType;
	newArc->start = n1;
	newArc->end = n2;

	addArc(newArc);
}


template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::addArc(ArcType* arc) {
	arcs.insert(arc);
	arc->start->arcs.insert(arc);
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeArc(const std::string& s1, const std::string& s2) {
	removeNode(nodeMap[s1], nodeMap[s2]);
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeArc(NodeType* n1, NodeType* n2) {
	for (ArcType* a : n1->arcs) {
		if (a->end == n2) {	//	a->startは必ずn1
			arcs->erase(a);
			n1->arcs.erase(a);
			delete a;
			a = nullptr;
			return;
		}
	}
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeArc(ArcType* arc) {
	NodeType* n1 = arc->start;
	for (ArcType* a : n1->arcs) {
		if (a == arc) {
			arcs.erase(a);
			n1->arcs.erase(a);
			delete a;
			a = nullptr;
			return;
		}
	}
}


template<typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isConnected(const std::string& s1, const std::string& s2) const {
	return isConnected(nodeMap[s1], nodeMap[s2]);
}


template<typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isConnected(NodeType* n1, NodeType* n2) const {
	for (ArcType* a : n1->arcs) {
		if (a->end == n2) {
			return true;
		}
	}

	return false;
}


template<typename NodeType, typename ArcType>
std::set<NodeType*>& Graph<NodeType, ArcType>::getNodeSet() const {
	return nodes;
}


template<typename NodeType, typename ArcType>
std::set<ArcType*>& Graph<NodeType, ArcType>::getArcSet() const {
	return arcs;
}

template<typename NodeType, typename ArcType>
std::set<ArcType*>& Graph<NodeType, ArcType>::getArcSet(const std::string& name) const {
	return nodeMap[name]->arcs;
}


template<typename NodeType, typename ArcType>
std::set<ArcType*>& Graph<NodeType, ArcType>::getArcSet(NodeType* node) const {
	return node->arcs;
}

template<typename NodeType, typename ArcType>
std::set<NodeType*> Graph<NodeType, ArcType>::getNeighbors(const std::string& name) const {
	return getNeighbors(nodeMap[name]);
}

template<typename NodeType, typename ArcType>
std::set<NodeType*> Graph<NodeType, ArcType>::getNeighbors(NodeType* node) const {
	std::set<NodeType*> s;
	for (ArcType* a : node->arcs) {
		s.insert(a->end);
	}

	return s;
}

template<typename NodeType, typename ArcType>
Graph<NodeType, ArcType>& Graph<NodeType, ArcType>::operator=(const Graph<NodeType, ArcType>& src) {
	if (this != &src) {	//	(*this!=src)はダメ。ポインタ変数を比較したほうが確実
		clear();
		deepCopy(src);
	}

	return *this;
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::deepCopy(const Graph<NodeType, ArcType>& src) {
	for (NodeType* n : src.nodes) {
		NodeType* nc = new NodeType;
		*nc = *n;
		nc->arcs.clear();
		addNode(nc);
	}

	for (ArcType* a : src.arcs) {
		ArcType* ac = new ArcType;
		*ac = *a;
		ac->start = nodeMap[a->start->name];
		ac->end = nodeMap[a->end->name];
		addArc(ac);
	}
}

template<typename NodeType, typename ArcType>
Vector<ArcType*> Graph<NodeType, ArcType>::findShortestPath(const std::string& startName, const std::string& endName) {
	return findShortestPath(nodeMap[startName], nodeMap[endName]);
}

//	ダイクストラ法:最短距離(コスト)の確定した点から最近傍点への合計距離(コスト)が最小となる点を確定する。これを繰り返す。
//	参考：https://www.youtube.com/watch?v=X1AsMlJdiok&list=LL&index=1
template<typename NodeType, typename ArcType>
Vector<ArcType*> Graph<NodeType, ArcType>::findShortestPath(NodeType* start, NodeType* end) {
	Vector<ArcType*> path;
	PQueue<Vector<ArcType*>> queue;
	std::set<NodeType*> confirmed;	//	最短距離(コスト)が確定したノードら

	NodeType* cp = start;
	while (cp != end) {
		if (!confirmed.contains(cp)) {
			confirmed.insert(cp);	//	コストは非負を前提としているので、cpへ向かうより短いパスはそれ以外に存在しないから確定できる

			//	新たに確定した点から最近傍点への合計距離を検討する
			for (ArcType* a : cp->arcs) {
				if (!confirmed.contains(a->end)) {
					path += a;
					queue.enqueue(path, getPathCost(path));
					path.remove(path.size() - 1);
				}
			}
		}

		if (queue.isEmpty()) {
			std::cerr << "ERROR : Vector<ArcType*> Graph::findShortestPath(NodeType* start, NodeType* end) : "
				<< "startからendへのパスが見つかりませんでした" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		path = queue.dequeue();	//	最短距離のパスを記録
		cp = path[path.size() - 1]->end;	//	最短距離が確定した点をcpへ
	}

	return path;
}

template<typename NodeType, typename ArcType>
double Graph<NodeType, ArcType>::getPathCost(Vector<ArcType*> path) const {
	double cost = 0;
	for (ArcType* a : path) {
		cost += a->cost;
	}
	return cost;
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::mapDFS(void (*fn)(NodeType*), NodeType* start) {
	std::set<NodeType*> visited;
	std::stack<NodeType*> s;
	s.push(start);

	while (!s.empty()) {
		NodeType* cp = s.top();
		s.pop();
		if (visited.contains(cp))continue;
		visited.insert(cp);

		fn(cp);

		for (ArcType* a : cp->arcs) {
			s.push(a->end);
		}
	}
}

template<typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::mapBFS(void (*fn)(NodeType*), NodeType* start) {
	std::set<NodeType*> visited;
	std::queue<NodeType*> q;
	q.push(start);

	while (!q.empty()) {
		NodeType* cp = q.front();
		q.pop();
		if (visited.contains(cp))continue;
		visited.insert(cp);

		fn(cp);

		for (ArcType* a : cp->arcs) {
			q.push(a->end);
		}
	}
}
