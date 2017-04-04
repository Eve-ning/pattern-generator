#pragma once
#ifndef FUNCTIONSDEBUG_H
#define FUNCTIONSDEBUG_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

//Just to print things
template<class TYPE>
void printDEBUG(std::string message, TYPE parameter);

//Debug Functions
void displayVector(std::vector<int> displayedVector);
void displayVector(std::vector<bool> displayedVector);

#endif // !FUNCTIONSDEBUG_H
