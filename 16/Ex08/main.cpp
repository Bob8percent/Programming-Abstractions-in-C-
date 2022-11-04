#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "Library/vector.h"
#include "BinarySearchTree.h"

int main() {
	BinarySearchTree bst;
	bst.insertNode("Sneezy");
	bst.insertNode("Sleepy");
	bst.insertNode("Happy");
	bst.insertNode("Bashful");
	bst.insertNode("Doc");
	bst.insertNode("Doppy");
	bst.insertNode("Grumpy");

	//bst.displayKey();
	bst.debug();
}
