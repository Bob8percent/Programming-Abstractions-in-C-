#include <iostream>
#include "BinarySearchTree.h"

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
	if (!node) {
		BSTNode* newNode = new BSTNode;
		newNode->key = key;
		newNode->left = nullptr;
		newNode->right = nullptr;
		node = newNode;
	}
	else {
		if (node->key != key) {
			if (node->key > key)insertNode(node->left, key);
			else insertNode(node->right, key);
		}
	}
}

void BinarySearchTree::displayKey(BSTNode* node) const {
	if (!node)return;

	displayKey(node->left);
	std::cout << node->key << std::endl;
	displayKey(node->right);
}
