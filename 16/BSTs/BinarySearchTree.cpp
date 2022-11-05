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

//	返り値は0または1。1は高さが変化したことを意味し、0は不変であることを意味する。	新nodeは必ずleafになるので、再帰によって上に高さの変化を伝えられる
//	insertのたびにAVLアルゴリズムによる回転を施すことで各ノードのbfを-1,0,1のどれかに保つ戦略。
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

		//	サブツリーの高さ不変
		if (delta == 0)return 0;

		//	末端左に挿入後の「node以下」の高さについて、bf=-1のとき不変(0返す)、bf=1のとき変化(1返す)、bf=0のとき変化(1返す)
		//	サブツリーの高さが変化した
		switch (node->bf) {
		case 1:
			node->bf = 0;
			return 0;
		case 0:
			node->bf = -1;
			return 1;
		case -1:
			fixLeftImBalance(node);
			return 0;
		}
	}
	else {
		int delta = insertAVL(node->right, key);

		//	サブツリーの高さ不変
		if (delta == 0) return 0;

		//	サブツリーの高さが変化した
		switch (node->bf) {
		case -1:
			node->bf = 0;
			return 0;
		case 0:
			node->bf = 1;
			return 1;
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
		node->bf = 0;
		child->bf = 0;
		rotateLeft(node);
	}
	else {
		int bf = child->left->bf;
		child->left->bf = 0;
		if (bf == 1) {
			child->bf = 0;
			node->bf = -1;
		}
		else if (bf == -1) {
			child->bf = 1;
			node->bf = 0;
		}
		else {
			child->bf = 0;
			node->bf = 0;
		}
		rotateRight(node->right);
		rotateLeft(node);
	}
}

void BinarySearchTree::fixLeftImBalance(BSTNode*& node) {
	BSTNode* child = node->left;
	
	//	教科書の図16-7のsingle rotationの方 : 同じ向きに伸長しているとき
	if (node->bf == child->bf) {
		node->bf = 0;
		child->bf = 0;
		rotateRight(node);
	}

	//	教科書の図16-7のdouble rotationの方 : 異なる向きに伸長しているとき
	else {
		//	図16-7のN3のbf
		int bf = child->right->bf;
		child->right->bf = 0;	//	N3
		if (bf == 1) {
			child->bf = -1;	//	N2
			node->bf = 0;	//	N1
		}
		else if (bf == -1) {
			child->bf = 0;
			node->bf = 1;
		}
		else {
			//	child nodeに新nodeが挿入されたとき
			//
			//	 node(-1)
			//   / 
			// child(1)
			//   \
			//   new!(0)
			child->bf = 0;
			node->bf = 0;
		}

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

//	O(logN)
int BinarySearchTree::height(BSTNode* node) const {
	//std::cout << node->key << " " << node->bf << std::endl;
	if (isLeaf(node))return 1;

	//	bfの正負で左右どちらのサブツリーを探索するかを決める(0のときはどちらでもいい)
	if (node->bf > 0) {
		return 1 + height(node->right);
	}
	else {
		return 1 + height(node->left);
	}
}

bool BinarySearchTree::isLeaf(BSTNode* node) const {
	return !(node->left) && !(node->right);
}

void BinarySearchTree::debug() {
	//std::cout << hasBinarySearchProperty(root) << std::endl;
	displayKey();
}

bool BinarySearchTree::isBalanced(BSTNode* node) const {
	return node->bf == 0;
}

//	2分探索木として整列されているか
bool BinarySearchTree::hasBinarySearchProperty(BSTNode* node) {

	BSTNode* left = node->left;
	BSTNode* right = node->right;
	bool isLeftCorrect = true;
	bool isRightCorrect = true;
	if (left)isLeftCorrect = (left->key < node->key);
	if (right)isRightCorrect = (node->key < right->key);

	if (left && !hasBinarySearchProperty(left))return false;
	if (right && !hasBinarySearchProperty(right))return false;

	//if (left && right)std::cout << left->key << " " << node->key << " " << right->key << std::endl;
	//else if (right)std::cout << "nullptr " << node->key << " " << right->key << std::endl;
	//else if (left)std::cout << left->key << " " << node->key << " nullptr" << std::endl;
	//else std::cout << "nullptr " << node->key << " nullptr" << std::endl;
	return isLeftCorrect && isRightCorrect;
}

