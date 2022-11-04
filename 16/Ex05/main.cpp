#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "Library/vector.h"
#include "FamilyTreeNode.h"

FamilyTreeNode* findStartNode(FamilyTreeNode* node, const std::string& name) {
	if (node->getName() == name)return node;

	Vector<FamilyTreeNode*> children = node->getChildren();
	for (int i = 0; i < children.size(); ++i) {
		FamilyTreeNode* result = findStartNode(children[i], name);
		if (result)return result;
	}

	return nullptr;
}

FamilyTreeNode* readFamilyTree(const std::string& filename) {
	//	ファイルのオープン
	std::ifstream ifs;
	ifs.open(filename);
	if (ifs.fail()) {
		std::cerr << "ERROR : FamilyTreeNode* readFamilyTree(const std::string& filename) : "
			<< "ファイルを開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	FamilyTreeNode* root = nullptr;
	std::string str;
	while (std::getline(ifs, str)) {
		//	親子関係にある名前を読み込む
		Vector<std::string> names;
		std::string name;
		for (int i = 0; i < str.length(); ++i) {
			char ch = str.at(i);
			if (ch == ':') {
				names += name;
				name.clear();
				continue;
			}
			name += ch;
			if (i == str.length() - 1) names += name;
		}

		//	root nodeの作成
		if (!root) {
			root = new FamilyTreeNode(names[names.size() - 1]);
		}
		if (names.size() <= 1)continue;	//	特にnames.size()==1のときはroot nodeを作成するときのみだが、その操作は一回だけに限定

		//	開始nodeまでcpを移動
		FamilyTreeNode* cp = findStartNode(root, names[names.size() - 1]);
		if (!cp) {
			std::cerr << "ERROR : FamilyTreeNode* readFamilyTree(const std::string& filename) : "
				<< names[names.size() - 1] << "に関して、startNodeが見つかりません" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		//	新nodeの追加
		for (int i = names.size() - 2; i >= 0; --i) {
			bool isFind = false;
			for (int k = 0; k < cp->getChildren().size(); ++k) {
				if (cp->getChildren()[k]->getName() == names[i]) {
					cp = cp->getChildren()[k];
					isFind = true;
					break;
				}
			}
			if (isFind)continue;

			FamilyTreeNode* newNode = new FamilyTreeNode(names[i]);
			cp->addChild(newNode);
			cp = newNode;
		}
	}

	return root;
}

void displayNode(FamilyTreeNode* node, int depth) {
	for (int i = 0; i < depth; ++i)std::cout << "  ";
	std::cout << node->getName() << std::endl;

	for (int i = 0; i < node->getChildren().size(); ++i) {
		displayNode(node->getChildren()[i], depth + 1);
	}
}

void displayNode(FamilyTreeNode* node) {
	displayNode(node, 0);
}

int main() {
	FamilyTreeNode* root = readFamilyTree("Normandy.txt");
	displayNode(root);


	FamilyTreeNode* p = commonAncestor(
		root->getChildren()[3]->getChildren()[0],	//	William
		root->getChildren()[3]->getChildren()[1]->getChildren()[0]);	//	Henry II
	std::cout << p->getName() << std::endl;	//	Henry I
}
