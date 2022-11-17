#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <stack>
#include <queue>
#include "_Graph.h"
#include "GraphTypes.h"
#include "TokenScanner.h"

void printAdjacencyLists(SimpleGraph& g) {
	for (std::pair<std::string, Node*> p : g.nodeMap) {//	g->nodesを使うとアドレス順になってしまう(要求順により大きいアドレスへヒープメモリを割り当てるとは限らない)
		std::cout << p.first << " -> ";

		Node* n = p.second;
		bool first = true;
		for (Arc* a : n->arcs) {
			if (!first)std::cout << ", ";
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

void addArc(SimpleGraph& g, const std::string& s1, const std::string& s2, double cost) {
	addArc(g, g.nodeMap[s1], g.nodeMap[s2], cost);
}

void readGraph(SimpleGraph& g, std::istream& is) {
	std::string line;
	while (std::getline(is, line)) {
		if (line == "")return;

		//	--------------------------------------------
		//	操作の方法を文字列から認識する
		std::size_t ypos = std::string::npos;	//	yの開始位置
		bool isArrow = false;	//	演算子は矢印であるか
		std::string x, y;
		int cost = 0;
		for (std::size_t i = 0; i < line.length(); ++i) {
			char ch = line.at(i);
			if (ch == '-') {
				x = line.substr(0, i - 1);	//	演算子の前後に空白があることを考慮。以降の操作に関しても同様

				isArrow = (line.at(i + 1) == '>');
				if (isArrow) ypos = i + 3;
				else ypos = i + 2;

				continue;
			}

			if (ch == '(') {
				y = line.substr(ypos, (i - ypos - 1));

				int digit = 1;
				for (std::size_t n = line.length() - 2; line.at(n) != ch; --n) {
					cost += digit * (line.at(n) - '0');	//	小数点があったときは知らん
					digit *= 10;
				}

				break;
			}
		}

		//	--------------------------------------------
		//	ハイフンが存在しないとき、ノードをグラフに含めるだけ
		if (ypos == std::string::npos) {
			addNode(g, line);
		}
		else {
			if (!g.nodeMap.contains(x))addNode(g, x);
			if (!g.nodeMap.contains(y))addNode(g, y);

			//	--------------------------------------------
			//	記号が矢印のとき、左辺をstartとするアークをグラフに含める
			addArc(g, x, y, cost);

			//	--------------------------------------------
			//	記号がハイフンのとき、両方向からのアークをグラフに含める
			if (!isArrow)addArc(g, y, x, cost);

		}

	}
}

void writeGraph(SimpleGraph& g, std::ostream& os) {
	std::set<std::string> doneSearch;	//	探索済みのArc
	for (Node* n : g.nodes) {
		for (Arc* a : n->arcs) {
			std::string x, y, cost;
			Node* n2 = a->end;

			//	-------------------------------------------
			//	探索済みのArcであるか調べる
			if (doneSearch.contains(n2->name + n->name))continue;
			doneSearch.insert(n->name + n2->name);

			//	-------------------------------------------
			//	x, y, costを求める
			x = n->name;
			y = n2->name;

			int c = a->cost;
			while (1) {
				cost = std::string(1, char('0' + c % 10)) + cost;
				c /= 10;
				if (c <= 0)break;
			}

			//	-------------------------------------------
			//	両方向アークかどうか
			bool isArrow = true;
			for (Arc* a2 : n2->arcs) {
				if (a2->end == n) {
					isArrow = false;
					break;
				}
			}
			std::string o;
			if (isArrow) o = " -> ";
			else o = " - ";

			//	-------------------------------------------
			//	osに出力
			os << x << o << y << " (" << cost << ")\n";
		}

	}
}
//
////	ループカウント：25
////	平均キュー長：5.64
//void breadthFirstSearch(Node* node) {
//	std::set<Node*> visited;
//	std::queue<Node*> q;
//	q.push(node);
//
//	double average = 0;
//	int count = 0;
//	while (!q.empty()) {
//		++count;
//		average += q.size();
//
//		Node* cp = q.front();
//		q.pop();
//
//		if (visited.contains(cp))continue;
//		visited.insert(cp);
//
//		for (Arc* a : cp->arcs) {
//			Node* n = a->end;
//			q.push(n);
//		}
//	}
//
//	std::cout << "ループカウント：" << count << std::endl;
//	std::cout << "平均キュー長：" << average / count << std::endl;
//}
//
//	平均キュー長：2.6
//	ループカウント：10
void breadthFirstSearch(Node* node) {
	std::set<Node*> visited;
	std::queue<Node*> q;
	q.push(node);
	visited.insert(node);

	double average = 0;
	int count = 0;
	while (!q.empty()) {
		++count;
		average += q.size();

		Node* cp = q.front();
		q.pop();

		for (Arc* a : cp->arcs) {
			Node* n = a->end;
			if (!visited.contains(n))q.push(n);
			else continue;
			visited.insert(n);
		}
	}

	std::cout << "ループカウント：" << count << std::endl;
	std::cout << "平均キュー長：" << average / count << std::endl;
}

std::string randomWord(int n = 8) {
	std::string word;
	for (int i = 0; i < n; ++i) {
		word += char(33 + rand() % 94);
	}

	return word;
}

void makeGraph(SimpleGraph& g, Node* parent, int depth) {
	if (depth <= 0)return;

	std::string name = randomWord();

	if (!parent) {
		addNode(g, "0");
		makeGraph(g, g.nodeMap["0"], depth - 1);
	}
	else {

		addNode(g, name);
		addArc(g, parent, g.nodeMap[name], 1);

		int en = 5;
		for (int i = 0; i < en; ++i) {
			makeGraph(g, g.nodeMap[name], depth - 1);
		}
	}
}

int main() {

	std::ifstream ifs;
	ifs.open("AirlineGraph.txt");
	if (ifs.fail()) {
		std::cerr << "ERROR : ファイルを開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	SimpleGraph airline;
	readGraph(airline, ifs);

	//printAdjacencyLists(airline);

	//std::cout << "---------------------------------" << std::endl;

	breadthFirstSearch(airline.nodeMap["Atlanta"]);

	ifs.clear();	//	フラグ解消

//	SimpleGraph g;
//	//makeGraph(g, nullptr, 10);
//
//	//printAdjacencyLists(g);
//
//	readGraph(g, );
//
//	double start = double(clock()) / CLOCKS_PER_SEC;
//	breadthFirstSearch(g.nodeMap["0"]);
//	double end = double(clock()) / CLOCKS_PER_SEC;
//	std::cout << end - start << std::endl;
}
