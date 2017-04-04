#include "functionsDEBUG.h"

//Displays the Vector <Debug Function>
//Input: (IVector) The Vector to display
void displayVector(std::vector<int> displayedVector)
{
	unsigned int displayedVectorSize = displayedVector.size();

	std::cout << "[DEBUG] Display Vector: ";

	for (unsigned int x = 0; x < displayedVectorSize; x++) {

		std::cout << displayedVector[x] << ",";

	}

	std::cout << std::endl;
}

//Displays the Vector <Debug Function>
//Input: (IVector) The Vector to display
void displayVector(std::vector<bool> displayedVector)
{

	unsigned int displayedVectorSize = displayedVector.size();

	std::cout << "[DEBUG] Display Vector: ";

	for (unsigned int x = 0; x < displayedVectorSize; x++) {

		std::cout << displayedVector[x] << ",";

	}

	std::cout << std::endl;

}

template<class TYPE>
void printDEBUG(std::string message, TYPE parameter)
{

	std::cout << "[" << message << "]: " << parameter << std::endl;

}