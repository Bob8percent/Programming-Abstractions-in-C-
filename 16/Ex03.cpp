#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "Library/vector.h"
#include "BinarySearchTree.h"

struct VectorTreeNode {
	std::string name;
	VectorTreeNode* sibling;	//	同世代の兄弟
	VectorTreeNode* child;
};

VectorTreeNode* findStartNode(VectorTreeNode* node, const std::string& name) {
	if (node->name == name)return node;
	
	VectorTreeNode* child = node->child;
	while (child) {
		VectorTreeNode* result = findStartNode(child, name);
		if (result)return result;

		child = child->sibling;
	}

	return nullptr;
}

VectorTreeNode* readFamilyTree(const std::string& filename) {
	//	ファイルのオープン
	std::ifstream ifs;
	ifs.open(filename);
	if (ifs.fail()) {
		std::cerr << "ERROR : FamilyTreeNode* readFamilyTree(const std::string& filename) : "
			<< "ファイルを開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	VectorTreeNode* root = nullptr;
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
			root = new VectorTreeNode;
			root->name = names[names.size() - 1];
			root->child = nullptr;
			root->sibling = nullptr;
		}
		if (names.size() <= 1)continue;	//	特にnames.size()==1のときはroot nodeを作成するときのみだが、その操作は一回だけに限定

		//	開始nodeまでcpを移動
		VectorTreeNode* cp = findStartNode(root, names[names.size() - 1]);
		if (!cp) {
			std::cerr << "ERROR : VectorTreeNode* readFamilyTree(const std::string& filename) : "
				<< names[names.size() - 1] << "に関して、startNodeが見つかりません" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		//	新nodeの追加
		VectorTreeNode** p = &cp;
		for (int i = names.size() - 2; i >= 0; --i) {
			//	新nodeの親を探索
			bool isFind = false;
			p = &((*p)->child);
			while (*p) {
				if ((*p)->name == names[i]) {
					isFind = true;
					break;
				}

				p = &((*p)->sibling);
			}
			if (isFind)continue;

			VectorTreeNode* newNode = new VectorTreeNode;
			newNode->name = names[i];
			newNode->sibling = nullptr;
			newNode->child = nullptr;
			*p = newNode;
		}
	}
	return root;
}

void displayNode(VectorTreeNode* node, int depth) {
	for (int i = 0; i < depth; ++i)std::cout << "  ";
	std::cout << node->name << std::endl;

	VectorTreeNode* child = node->child;
	while (child) {
		displayNode(child, depth + 1);
		child = child->sibling;
	}
}

void displayNode(VectorTreeNode* node) {
	displayNode(node, 0);
}

int main() {
	VectorTreeNode* root = readFamilyTree("Normandy.txt");
	displayNode(root);
}

