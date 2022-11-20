#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "graphpriv.h"
#include "Library/vector.h"

//	グラフを使ったルーティングアレイの更新

int main() {
	std::ifstream ifs;
	ifs.open("C18Ex15.txt");
	if (ifs.fail()) {
		std::cerr << "ERROR : ファイルを開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	Graph<ARPAnode, ARPAarc> g;
	g.readGraph(ifs);

	//	初期化
	std::set<ARPAnode*> nodes = g.getNodeSet();
	for (ARPAnode* n : nodes) {
		n->initializeArray(nodes);
	}

	//	送信
	bool isAllComplete = false;
	while (!isAllComplete) {	//	終了条件はすべてのルーティングアレイに未確定の要素がなくなるときにしたが、それでいいのかよくわからない
		isAllComplete = true;
		for (ARPAnode* n : nodes) {
			if (!n->isComplete())isAllComplete = false;
			
			//	隣接ノードへ送信
			for (ARPAarc* a : n->getArcs()) {
				a->getEnd()->receiveArray(n->getArray());
			}
		}
	}

	for (ARPAnode* n : nodes) {
		n->debug();
	}
}
