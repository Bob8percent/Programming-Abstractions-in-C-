#pragma once
#include <string>
#include <set>
#include <map>
#include "_Graph.h"

//	Node, Arcをユーザーが定義する戦略を実装したが、これだとGraph特有の処理に合わせないといけない(setや変数の名前、friendの使用など)ので
//	ユーザーはGraphの内部処理を知ってないとGraphを使えず、結局不便だと思う。

//	前方参照
class City;
class Flight;

//	Graphにおけるnodeに対応
class City {
public:
	std::string getName() const { return name; }
	void setCode(const std::string airportCode) { this->airportCode = airportCode; }

private:
	std::string name;
	std::set<Flight*> arcs;
	std::string airportCode;
	friend class Graph<City, Flight>;	//	Graphクラスにインスタンスへのアクセスを許可
};

//	Graphにおけるarcに対応
class Flight {
public:
	std::string getStartName() const { return start->getName(); }
	std::string getEndName() const { return end->getName(); }
	int getCost() const { return cost; }
	void setCost(int cost) { this->cost = cost; }

private:
	City* start;
	City* end;
	int cost;
	friend class Graph<City, Flight>;
};

//	-----------------------------------------------------------------------------------------------
//	Chapter18 Ex15に関するクラス

class ARPAnode;
class ARPAarc;

class ARPAnode {
public:
	std::string getName() const { return name; }

	//	隣接ノードからルーティングアレイを取得
	void receiveArray(std::map<ARPAnode*, int> m) {
		for (std::pair<ARPAnode*, int> p : routingMap) {
			int mh = m[p.first];
			int& h = routingMap[p.first];
			if (h == -1 && mh != -1)h = mh + 1;

			if (h != -1 && mh != -1 && mh < h)h = mh + 1;
		}
	}

	//	ルーティングアレイを初期化
	void initializeArray(std::set<ARPAnode*> s) {
		for (ARPAnode* n : s) {
			routingMap[n] = -1;
			if (n == this)routingMap[n] = 0;
		}
	}

	//	ルーティングアレイが完成しているか
	bool isComplete(){
		for (std::pair<ARPAnode*, int> p : routingMap) {
			if (p.second == -1)return false;
		}
		return true;
	}

	void debug() {
		std::cout << name << std::endl;
		for (std::pair<ARPAnode*, int> p : routingMap) {
			std::cout << p.first->getName() << " : " << p.second << ", ";
		}
		std::cout << std::endl;
	}

	std::set<ARPAarc*>& getArcs() { return arcs; }
	std::map<ARPAnode*, int>& getArray(){ return routingMap; }

private:
	std::string name;
	std::set<ARPAarc*> arcs;

	//	ルーティングアレイ：各ノードのホップ数を示す
	std::map<ARPAnode*, int> routingMap;
	
	friend class Graph<ARPAnode, ARPAarc>;
};

class ARPAarc {
public:
	std::string getStartName() const { return start->getName(); }
	std::string getEndName() const { return end->getName(); }
	int getCost() const { return cost; }
	void setCost(int cost) { this->cost = cost; }

	ARPAnode* getStart() const { return start; }
	ARPAnode* getEnd() const { return end; }

private:
	ARPAnode* start;
	ARPAnode* end;
	int cost;
	friend class Graph<ARPAnode, ARPAarc>;
};
