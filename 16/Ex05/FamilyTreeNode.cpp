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

bool FamilyTreeNode::operator==(const FamilyTreeNode& src) {
	return name == src.name;
}

FamilyTreeNode* commonAncestor(FamilyTreeNode* p1, FamilyTreeNode* p2) {
	FamilyTreeNode* p1p = p1->getParent();	//	p1の祖先
	while (p1p) {
		FamilyTreeNode* p2p = p2->getParent();
		while (p2p) {
			if ((*p1p) == (*p2p))return p1p;
			p2p = p2p->getParent();
		}

		p1p = p1p->getParent();
	}
}


