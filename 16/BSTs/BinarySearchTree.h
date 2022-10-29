#pragma once
#include <string>

//	二分探索木：常に整列された二分木
class BinarySearchTree
{
public:
	struct BSTNode {
		std::string key;
		BSTNode* left;
		BSTNode* right;
	};

	BSTNode* findNode(BSTNode* node, const std::string& key) const;
	void insertNode(BSTNode*& node, const std::string& key);

	void displayKey(BSTNode* node) const;

private:

	

};

