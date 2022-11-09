#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "_PQueue.h"

int main() {
	PQueue<std::string> p;

	p.enqueue("aaa", 2708);
	p.enqueue("bbb", 3169);
	p.enqueue("ccc", 1604);
	p.enqueue("ddd", 1861);
	p.enqueue("eee", 2193);

	while (!p.isEmpty()) {
		std::cout << p.dequeue() << std::endl;
		p.debug();
		std::cout << std::endl;
	}
}
