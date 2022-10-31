#include <iostream>
#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
	clear(root);
}

void BinarySearchTree::insertNode(const std::string& key) {
	insertNode(root, key);
}

BinarySearchTree::BSTNode* 
BinarySearchTree::findNode(BSTNode* node, const std::string& key) const {
	if (!node)return nullptr;
	else if (node->key == key)return node;
	
	if (node->key > key)return findNode(node->left, key);
	else return findNode(node->right, key);
}

//	pointer渡しだとポインタ先は変更されるが実引数は変更されない(つまり値渡し)。
//	実引数のポインタ変数を更新するために参照渡しする
void BinarySearchTree::insertNode(BSTNode*& node, const std::string& key) {
	insertAVL(node, key);
}

//	返り値は0または1。1は新しいノードが追加されたので木が要更新であることを意味する。0は更新しなくてもよいことを意味する。
int BinarySearchTree::insertAVL(BSTNode*& node, const std::string& key) {
	if (!node) {
		node = new BSTNode;
		node->bf = 0;
		node->key = key;
		node->right = nullptr;
		node->left = nullptr;

		return 1;
	}

	if (node->key == key)return 0;
	else if (node->key > key) {
		int delta = insertAVL(node->left, key);

		//	更新の必要なし
		if (delta == 0)return 0;

		//	更新する必要あり
		switch (node->bf) {
		case 1:
			node->bf = 0;
			return 0;
		case 0:
			node->bf = -1;
			return 1;	//	返り値は0以外であればなんでもOK
		case -1:
			fixLeftImBalance(node);
			return 0;
		}
	}
	else {
		int delta = insertAVL(node->right, key);

		//	更新の必要なし
		if (delta == 0) return 0;

		//	更新する必要あり
		switch (node->bf) {
		case -1:
			node->bf = 0;
			return 0;
		case 0:
			node->bf = 1;
			return 1;	//	返り値は0以外であればなんでもOK
		case 1:
			fixRightImBalance(node);
			return 0;
		}
	}
}

//	右の高さが左より2だけ高いサブツリーを修正する。nodeはサブツリーのルートノード
void BinarySearchTree::fixRightImBalance(BSTNode*& node) {
	BSTNode* child = node->right;
	if (node->bf == child->bf) {
		//	一回の回転で十分
		rotateLeft(node);
		node->bf = 0;
		child->bf = 0;
	}
	else {
		int bf = child->left->bf;
		child->bf = 0;
		child->left->bf = 0;
		if (bf == 0) node->bf = 0;
		else node->bf = 1;
		rotateRight(node->right);
		rotateLeft(node);
	}
}

void BinarySearchTree::fixLeftImBalance(BSTNode*& node) {
	BSTNode* child = node->left;
	if (node->bf == child->bf) {
		//	考えられるのは以下の場合だけ
		// 
		//       node(-1)
		//       /
		//    child(-1)
		//     /
		//   new!
		// 
		//	よって一回の回転で十分
		rotateRight(node);
		node->bf = 0;
		child->bf = 0;
	}
	else {
		//	fixLeftImBalance()はchild->rightに挿入されたときにしか呼ばれない。
		//	つまり、child->bf==-1、node->bf==1の時以外考えられない。
		// 
		//	以下の3通りが考えられる(()は関数呼び出し時のbf)
		// 
		//      node(-1)             node(-1)                 node(-1)
		//      /    \               /    \                   / 
		//  child(1)  other      child(1)  other           child(1)
		//   /   \           or    /   \           or         \
		// other other          other  other                  new!
		//        /                      \
		//      new!                     new!
		//
		int bf = child->right->bf;
		//	上の三種類に共通した処理
		child->bf = 0;
		child->right->bf = 0;

		//	3つ目特有の処理
		if (bf == 0) node->bf = 0;

		//	1, 2つ目特有の処理
		else node->bf = -1;

		rotateLeft(node->left);
		rotateRight(node);
	}
}

//	fixRight/LeftImBalance()でのみ使われることを想定している
//	時計回り
void BinarySearchTree::rotateRight(BSTNode*& node) {
	BSTNode* child = node->left;
	node->left = child->right;
	child->right = node;


	//	以下の処理は、ヒープ領域のBSTNodeらの中身の変更だけでなく、(メモリのスタック領域にある)インスタンス変数rootを変更するため。
	//	これをしないとrootは(スタック領域にあるので)ずっと最初にinsertしたノードを参照したままになり、意図した処理にならない。
	node = child;
}

//	反時計回り
void BinarySearchTree::rotateLeft(BSTNode*& node) {
	BSTNode* child = node->right;
	node->right = child->left;	//	childにleftがあったときはnode->rightへ移す。ないときは関係ない。
	child->left = node;
	node = child;
}

void BinarySearchTree::displayKey() const {
	displayKey(root);
}

//	inorder traversal
void BinarySearchTree::displayKey(BSTNode* node) const {
	if (!node)return;

	displayKey(node->left);
	std::cout << node->key << std::endl;
	displayKey(node->right);
}

void BinarySearchTree::clear(BSTNode* node) {
	if (!node)return;
	clear(node->left);
	clear(node->right);
	delete node;
}
