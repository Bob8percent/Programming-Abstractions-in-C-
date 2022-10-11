#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/stack.h"
#include "CharStack.h"
#include "UnitTest.h"

class Student {
public:
	Student() {
		id = 0;
		gpa = 4.0;
	}

	Student(int id, double gpa) {
		std::cout << "&id : " << &id << std::endl;
		std::cout << "&gpa : " << &gpa << std::endl;
		std::cout << "&this->id : " << &this->id << std::endl;
		std::cout << "&this->gpa : " << &this->gpa << std::endl;
		this->id = id;
		this->gpa = gpa;
	}

private:
	int id;
	double gpa;
};

int main() {
	Student* advisees = new Student[2];
	std::cout << "advisees : " << advisees << std::endl;
	std::cout << "&advisees : " << &advisees << std::endl;
	advisees[0] = Student(2718281, 3.61);
	advisees[1] = Student(3141592, 4.2);

}




