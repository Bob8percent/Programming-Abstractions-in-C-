#pragma once
#include <set>
#include <map>
#include <string>

//	前方参照：「実体」を持つ場合は「定義」が必要だが、「ポインタ」を持つ場合は「宣言」だけでよい.関数の返り値や引数の型として用いる場合も宣言でOK
struct Node;
struct Arc;

struct SimpleGraph {
	//	setを用いるのは、コーディング上有利になるという経験則と、和集合や積集合を使用できる点
	std::set<Node*> nodes;
	std::set<Arc*> arcs;
	std::map<std::string, Node*> nodeMap;	//	nodeとその名前をペアとするmap
};

struct Node {
	std::string name;
	std::set<Arc*> arcs;	//	隣接リスト
};

struct Arc {
	Node* start;
	Node* end;
	double cost;
};
