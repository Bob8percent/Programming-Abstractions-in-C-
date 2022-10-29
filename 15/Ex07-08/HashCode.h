#pragma once
#include <string>

template <typename Type>
bool isPrimitive(const Type& t) {
	return (typeid(Type) == typeid(std::string))
		|| (typeid(Type) == typeid(char))
		|| (typeid(Type) == typeid(int))
		|| (typeid(Type) == typeid(bool))
/*		|| (typeid(Type) == float)
		|| (typeid(Type) == double)*/;
}

int hashCode(const std::string& key);
int hashCode(char key);
int hashCode(int key);
int hashCode(bool key);

//	TODO
//int hashCode(float key);
//int hashCode(double key);
