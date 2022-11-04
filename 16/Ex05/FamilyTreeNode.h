#pragma once
#include <string>
#include "Library/vector.h"

class FamilyTreeNode
{
public:
	FamilyTreeNode(const std::string& name);
	std::string getName() const;
	void addChild(FamilyTreeNode* child);
	FamilyTreeNode* getParent() const;
	const Vector<FamilyTreeNode*>& getChildren() const;

	bool operator==(const FamilyTreeNode& src);

private:
	std::string name;
	FamilyTreeNode* parent; 
	Vector<FamilyTreeNode*> children;
};

FamilyTreeNode* commonAncestor(FamilyTreeNode* p1, FamilyTreeNode* p2);

