#include "FamilyTreeNode.h"

FamilyTreeNode::FamilyTreeNode(const std::string& name) {
	this->name = name;
	parent = nullptr;
}

std::string FamilyTreeNode::getName() const {
	return name;
}

void FamilyTreeNode::addChild(FamilyTreeNode* child) {
	children += child;
	child->parent = this;
}

FamilyTreeNode* FamilyTreeNode::getParent() const {
	return parent;
}

const Vector<FamilyTreeNode*>& FamilyTreeNode::getChildren() const {
	return children;
}

