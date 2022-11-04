#pragma once
#include <string>

//	二分探索木：常に整列された二分木
class BinarySearchTree
{
public:
	struct BSTNode {
		int bf;	//	balance factor(右のサブツリーの高さ - 左のサブツリーの高さ)
		std::string key;
		BSTNode* left;
		BSTNode* right;
	};

	BinarySearchTree();
	~BinarySearchTree();

	void displayKey() const;

	//BSTNode* findNode(BSTNode* node, const std::string& key) const;
	void insertNode(const std::string& key);

	void debug();

private:
	BSTNode* findNode(BSTNode* node, const std::string& key) const;
	void insertNode(BSTNode*& node, const std::string& key);
	int insertAVL(BSTNode*& node, const std::string& key);
	void fixRightImBalance(BSTNode*& node);
	void fixLeftImBalance(BSTNode*& node);
	void rotateRight(BSTNode*& node);
	void rotateLeft(BSTNode*& node);

	void displayKey(BSTNode* node) const;

	void clear(BSTNode* node);

	int height(BSTNode* node) const;
	bool isLeaf(BSTNode* node) const;

	bool isBalanced(BSTNode* node) const;

	BSTNode* root;
};

