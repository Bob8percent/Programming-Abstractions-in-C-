#pragma once
#include <string>
#include <iostream>

//	二分探索木：常に整列された二分木
template <typename KeyType, typename ValueType>
class BinarySearchTree
{
public:
	struct BSTNode {
		int color;	//	0がblack, 1がred
		KeyType key;
		ValueType value;
		BSTNode* left;
		BSTNode* right;
	};

	BinarySearchTree();
	~BinarySearchTree();

	void displayKey() const;

	void insertNode(const KeyType& key, const ValueType& value);
	
	void removeNode(const KeyType& key);

	ValueType& getValue(const KeyType& key) const;
	bool containsKey(const KeyType& key) const;

	int size() const;

	void debug();

private:
	BSTNode* findNode(BSTNode* node, const KeyType& key) const;

	int insert(BSTNode*& node, const KeyType& key, const ValueType& value);
	BSTNode* remove(BSTNode*& node, int& direction, const KeyType& key);
	int reBalance(BSTNode*& node, const BSTNode* actionPos, const int direction);
	int leftReBalance(BSTNode*& actionPos);
	int rightReBalance(BSTNode*& actionPos);

	void fixRightImBalance(BSTNode*& node, int delta);
	void fixLeftImBalance(BSTNode*& node, int delta);
	void rotateRight(BSTNode*& node);
	void rotateLeft(BSTNode*& node);

	void displayKey(BSTNode* node, int height) const;

	void clear(BSTNode* node);

	int height(BSTNode* node) const;
	bool isLeaf(BSTNode* node) const;

	bool hasBinarySearchProperty(BSTNode* tree);

	void deepCopy(const BinarySearchTree& src);
	void deepCopy(BSTNode*& node, const BSTNode* srcNode);

	BSTNode* root;
	int count;
};

template <typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::BinarySearchTree() {
	root = nullptr;
	count = 0;
}

template <typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::~BinarySearchTree() {
	clear(root);
}

template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::insertNode(const KeyType& key, const ValueType& value) {
	insert(root, key, value);
}

template <typename KeyType, typename ValueType>
ValueType& BinarySearchTree<KeyType, ValueType>::getValue(const KeyType& key) const {
	BSTNode* result = findNode(root, key);
	if (result)return result->value;
	else {
		std::cerr << "ERROR : ValueType & BinarySearchTree::getValue(const KeyType & key) const : "
			<< "要素が見つかりません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

template <typename KeyType, typename ValueType>
bool BinarySearchTree<KeyType, ValueType>::containsKey(const KeyType& key) const {
	return findNode(root, key);
}

template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::BSTNode*
BinarySearchTree<KeyType, ValueType>::findNode(BSTNode* node, const KeyType& key) const {
	if (!node)return nullptr;
	else if (node->key == key)return node;

	if (node->key > key)return findNode(node->left, key);
	else return findNode(node->right, key);
}

template <typename KeyType, typename ValueType>
int BinarySearchTree<KeyType, ValueType>::size() const {
	return count;
}

const int INSERT_L = 21;
const int INSERT_R = 11;
//	1はred, INSERT_Rはred-(r)red, INSERT_Lはred-(l)redを表している
template <typename KeyType, typename ValueType>
int BinarySearchTree<KeyType, ValueType>::insert(BSTNode*& node, const KeyType& key, const ValueType& value) {
	if (!node) {
		BSTNode* tmp = new BSTNode;
		if (root)tmp->color = 1;	//	red
		else tmp->color = 0;	//	black
		node = tmp;
		node->key = key;
		node->value = value;
		node->right = nullptr;
		node->left = nullptr;
		++count;

		return 1;
	}

	if (node->key == key)return 0;
	else if (node->key > key) {
		int delta = insert(node->left, key, value);

		//	node->leftとnodeが赤の場合
		if (delta == 1 && node->color == 1) {
			return INSERT_L;
		}
		//	nodeが黒の場合
		if (node->color == 0 && (delta == INSERT_R || delta == INSERT_L)) {
			fixLeftImBalance(node, delta);
			return 1;	//	nodeは赤となるので1を返す
		}

		return 0;
	}
	else {
		int delta = insert(node->right, key, value);

		//	node->rightとnodeが赤の場合
		if (delta == 1 && node->color == 1) {
			return INSERT_R;
		}
		//	nodeが黒の場合
		if (node->color == 0 && (delta == INSERT_R || delta == INSERT_L)) {
			fixRightImBalance(node, delta);
			return 1;	//	nodeは赤となるので1を返す
		}

		return 0;
	}
}

template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::removeNode(const KeyType& key) {
	
	int direction = 0;
	BSTNode* actionPos = remove(root, direction, key);	//	削除と入れ替え.actionPosを返す

	if (!actionPos || direction == 0 || direction == 3)return;

	//	黒が削除されたときはリバランス
	reBalance(root, actionPos, direction);
}

//	actionPosを返す。directionについて、0のとき赤または未削除、1のときleftの黒、2のときrightの黒、3のとき単に黒が削除されたことを意味する
template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::BSTNode*
BinarySearchTree<KeyType, ValueType>::remove(BSTNode*& node, int& direction, const KeyType& key) {
	if (!node) return nullptr;

	if (node->key == key) {
		//	赤を消すとき
		//	赤黒木の定義より赤色となるのはleafまたは2つの子をもつノードのみ。
		//	2つの子をもつノードについて、削除するのは入れ替え対象であるので、結果的にleafまたは1つ子をもつ黒ノードを削除する。
		
		//	1. nodeがleafのとき
		if (isLeaf(node)) {
			bool isRed = (node->color == 1);
			delete node;
			node = nullptr;
			if (isRed) return nullptr;
		}

		//	2. nodeが2つの子をもつとき
		else if (node->right && node->left) {
			BSTNode** cp = nullptr;	//	入れ替え対象を見つける
			BSTNode* actionPos = nullptr;
			cp = &node->left;
			actionPos = node;
			direction = 1;
			while ((*cp)->right) {
				direction = 2;
				actionPos = (*cp);
				cp = &(*cp)->right;
			}
			bool isRed = ((*cp)->color == 1);

			node->key = (*cp)->key;

			BSTNode* r = (*cp)->left;
			delete (*cp);
			(*cp) = r;

			if (isRed) {
				direction = 0;
				return nullptr;
			}
			return actionPos;
		}

		//	3. nodeが1つのみ子をもつとき
		else if (node->right) {
			BSTNode* right = node->right;
			delete node;
			node = right;
		}
		else if (node->left) {
			BSTNode* left = node->left;
			delete node;
			node = left;
		}

		direction = 3;
	}
	else if (node->key > key) {
		return remove(node->left, direction, key);
	}
	else {
		return remove(node->right, direction, key);
	}

	return nullptr;
}

//	手順：http://wwwa.pikara.ne.jp/okojisan/rb-tree/index.html
const int REMOVE_1 = 31;
const int REMOVE_2 = 41;
const int REMOVE_3 = 51;
const int REMOVE_4 = 61;
//	remove後のバランスを補正する
//	bfが変化する可能性があるのはrootからactionPosまで
template <typename KeyType, typename ValueType>
int BinarySearchTree<KeyType, ValueType>::reBalance(BSTNode*& node, const BSTNode* actionPos, const int direction) {
	if (!node) {
		std::cerr << "ERROR : void BinarySearchTree::reBalance(BSTNode*& node, const BSTNode* actionPos, const int direction) : "
			<< "actionPosが見つかりません" << std::endl;
		return 0;
	}

	if (node->key == actionPos->key) {
		//	nodeのleftの子が削除された
		if (direction == 1) {
			return rightReBalance(node);
		}

		//	nodeのrightの子が削除された
		else if (direction == 2) {
			return leftReBalance(node);
		}
	}
	else if (node->key > actionPos->key) {
		int delta = reBalance(node->left, actionPos, direction);

		if (delta == 0)return 0;

		rightReBalance(node);
	}
	else {
		int delta = reBalance(node->right, actionPos, direction);

		if (delta == 0)return 0;

		leftReBalance(node);
	}
}

template <typename KeyType, typename ValueType>
int BinarySearchTree<KeyType, ValueType>::leftReBalance(BSTNode*& actionPos) {
	BSTNode* child = actionPos->left;
	while (child) {
		if (child->color == 0) {
			if (child->right && child->right->color == 1) {
				fixLeftImBalance(actionPos, REMOVE_1);
			}
			else if (child->left && child->left->color == 1) {
				fixLeftImBalance(actionPos, REMOVE_2);
			}
			else {
				bool isBlack = (actionPos->color == 0);
				fixLeftImBalance(actionPos, REMOVE_3);
				if (isBlack)return 1;	//	黒の数が変化(一つ減る)
			}	

			return 0;	//	actionPosを根とする木の黒の数は変わらない
		}
		else {
			fixLeftImBalance(actionPos, REMOVE_4);
			child = actionPos->right->left;
			if (child->color == 0) {
				if (child->right && child->right->color == 1) {
					fixRightImBalance(actionPos->right, REMOVE_1);
				}
				else if (child->left && child->left->color == 1) {
					fixRightImBalance(actionPos->right, REMOVE_2);
				}
				else {
					bool isBlack = (actionPos->right->color == 0);
					fixRightImBalance(actionPos->right, REMOVE_3);
					if (isBlack)return 1;	//	黒の数が変化(一つ減る)
				}
			}
			return 0;
		}
	}
}

template <typename KeyType, typename ValueType>
int BinarySearchTree<KeyType, ValueType>::rightReBalance(BSTNode*& actionPos) {
	BSTNode* child = actionPos->right;
	if (child->color == 0) {
		if (child->left && child->left->color == 1) {
			fixRightImBalance(actionPos, REMOVE_1);
		}
		else if (child->right && child->right->color == 1) {
			fixRightImBalance(actionPos, REMOVE_2);
		}
		else {
			bool isBlack = (actionPos->color == 0);
			fixRightImBalance(actionPos, REMOVE_3);
			if (isBlack)return 1;	//	黒の数が変化(一つ減る)
		}

		return 0;	//	actionPosを根とする木の黒の数は変わらない
	}
	else {
		fixRightImBalance(actionPos, REMOVE_4);
		child = actionPos->left->right;
		if (child->color == 0) {
			if (child->left && child->left->color == 1) {
				fixRightImBalance(actionPos->left, REMOVE_1);
			}
			else if (child->right && child->right->color == 1) {
				fixRightImBalance(actionPos->left, REMOVE_2);
			}
			else {
				bool isBlack = (actionPos->left->color == 0);
				fixRightImBalance(actionPos->left, REMOVE_3);
				if (isBlack)return 1;	//	黒の数が変化(一つ減る)
			}
		}
		return 0;
	}
}

//	右の高さが左より2だけ高いサブツリーを修正する。nodeはサブツリーのルートノード
template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::fixRightImBalance(BSTNode*& node, int delta) {
	BSTNode* child = node->right;

	//     node(B)
	//       \
	//      child(R)
	//         \
	//        child(R)
	if (delta == INSERT_R) {
		node->color = 0;
		if (node->key == root->key)child->color = 0;
		else child->color = 1;
		child->right->color = 0;
		rotateLeft(node);
	}

	//     node(B)
	//       \
	//      child(R)
	//        /
	//     child(R)
	else if (delta == INSERT_L) {
		node->color = 0;
		child->color = 0;
		if (node->key == root->key)child->left->color = 0;
		else child->left->color = 1;
		rotateRight(node->right);
		rotateLeft(node);
	}

	//       node(R/B)
	//          \
	//         child(B)
	//          /
	//       node(R)
	else if (delta == REMOVE_1) {
		child->left->color = node->color;
		node->color = 0;
		child->color = 0;
		rotateRight(node->right);
		rotateLeft(node);
	}

	//        node(R/B)
	//           \
	//          child(B)
	//             \
	//            node(R)
	else if (delta == REMOVE_2) {
		child->color = node->color;
		node->color = 0;
		child->right->color = 0;
		rotateLeft(node);
	}

	else if (delta == REMOVE_3) {
		node->color = 0;
		child->color = 1;
	}

	else if (delta == REMOVE_4) {
		node->color = 1;
		child->color = 0;
		rotateLeft(node);
	}
}

template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::fixLeftImBalance(BSTNode*& node, int delta) {
	BSTNode* child = node->left;

	//	nodeとchildが同じ向きに伸長しているとき
	//      node(B)
	//     /
	//   child(R)
	//   /
	// child(R)
	if (delta == INSERT_L) {
		node->color = 0;
		if (node->key == root->key)child->color = 0;
		else child->color = 1;
		child->left->color = 0;
		rotateRight(node);
	}

	//	nodeとchildが異なる向きに伸長しているとき
	//      node(B)
	//     /
	//   child(R)
	//     \
	//    child(R)
	else if (delta == INSERT_R) {
		node->color = 0;
		child->color = 0;
		if (node->key == root->key)child->right->color = 0;
		else child->right->color = 1;
		rotateLeft(node->left);
		rotateRight(node);
	}

	//       node(R/B)
	//          /
	//      child(B)
	//          \
	//       node(R)
	else if (delta == REMOVE_1) {
		child->right->color = node->color;
		node->color = 0;
		child->color = 0;
		rotateLeft(node->left);
		rotateRight(node);
	}

	//        node(R/B)
	//           /
	//       child(B)
	//         /
	//      node(R)
	else if (delta == REMOVE_2) {
		child->color = node->color;
		node->color = 0;
		child->left->color = 0;
		rotateRight(node);
	}

	else if (delta == REMOVE_3) {
		node->color = 0;
		child->color = 1;
	}

	else if (delta == REMOVE_4) {
		node->color = 1;
		child->color = 0;
		rotateRight(node);
	}
}

//	fixRight/LeftImBalance()でのみ使われることを想定している
//	時計回り
template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::rotateRight(BSTNode*& node) {
	BSTNode* child = node->left;
	node->left = child->right;
	child->right = node;

	//	以下の処理は、ヒープ領域のBSTNodeらの中身の変更だけでなく、(メモリのスタック領域にある)インスタンス変数rootを変更するため。
	//	これをしないとrootは(スタック領域にあるので)ずっと最初にinsertしたノードを参照したままになり、意図した処理にならない。
	node = child;
}

//	反時計回り
template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::rotateLeft(BSTNode*& node) {
	BSTNode* child = node->right;
	node->right = child->left;	//	childにleftがあったときはnode->rightへ移す。ないときは関係ない。
	child->left = node;
	node = child;
}

template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::displayKey() const {
	displayKey(root, 0);
}

//	inorder traversal
template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::displayKey(BSTNode* node, int height) const {
	if (!node)return;

	displayKey(node->right, 1 + height);
	for (int i = 0; i < height; ++i)std::cout << "  ";
	std::cout << node->key << "(" << (node->color ? 'R' : 'B') << ")" << std::endl;
	displayKey(node->left, 1 + height);
}

template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::clear(BSTNode* node) {
	if (!node)return;
	clear(node->left);
	clear(node->right);
	delete node;
	count = 0;
}

//	O(logN)
template <typename KeyType, typename ValueType>
int BinarySearchTree<KeyType, ValueType>::height(BSTNode* node) const {
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

template <typename KeyType, typename ValueType>
bool BinarySearchTree<KeyType, ValueType>::isLeaf(BSTNode* node) const {
	return !(node->left) && !(node->right);
}

template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::debug() {
	//std::cout << hasBinarySearchProperty(root) << std::endl;
	displayKey();
	std::cout << std::endl;

	removeNode("Happy");
	displayKey();
	std::cout << std::endl;

	removeNode("Doppy");
	displayKey();
}

//	2分探索木として整列されているか
template <typename KeyType, typename ValueType>
bool BinarySearchTree<KeyType, ValueType>::hasBinarySearchProperty(BSTNode* node) {

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

template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::deepCopy(const BinarySearchTree& src) {
	deepCopy(root, src.root);
}

template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::deepCopy(BSTNode*& node, const BSTNode* srcNode) {
	if (!srcNode)return;

	node = new BSTNode;
	node->bf = srcNode->bf;
	node->key = srcNode->key;
	node->value = srcNode->value;
	node->right = nullptr;
	node->left = nullptr;

	deepCopy(node->right, srcNode->right);
	deepCopy(node->left, srcNode->left);
}



