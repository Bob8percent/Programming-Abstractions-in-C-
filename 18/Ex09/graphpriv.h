#pragma once
#include <string>
#include <set>
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
	int getDistance() const { return distance; }
	void setDistance() { this->distance = distance; }

private:
	City* start;
	City* end;
	int distance;
	friend class Graph<City, Flight>;

};
