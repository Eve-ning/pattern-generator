#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "functionsDEBUG.h"
#include "functions.h"
#include "ManiaLib\Input_Validator.h"
#include "ManiaLib\Compiler.h"

int main() {

	int pause;

	manialib_input_validator::Input_Validator INPUT_VALIDATOR;
	manialib_compiler::Compiler COMPILER;

	//Generates the Chart
	std::vector< std::vector<bool> > fullChartVector;
	int keys;
	int numberOfGenerations;
	int numberOfNotesBuffer;
	int anchor_limit;
	std::vector<int> numberOfNotes;
	double BPM;
	int snap;
	int offset;

	srand(time(NULL));

	/*std::cout << "Input the number of rows generated ";
	numberOfGenerations = INPUT_VALIDATOR.Input_Value_I(1, 100000, true);

	std::cout << "Input the number of keys ";
	keys = INPUT_VALIDATOR.Input_Value_I(1, 18, true);

	std::cout << "Input the maximum number of anchors ";
	anchor_limit = INPUT_VALIDATOR.Input_Value_I(1, 10, true);

	std::cout << "Input the note count pattern <Type -1 to stop input> " << std::endl;
	numberOfNotesBuffer = INPUT_VALIDATOR.Input_Value_I(-1, keys, true);

	while (numberOfNotesBuffer != -1) {

		numberOfNotes.push_back(numberOfNotesBuffer);
		numberOfNotesBuffer = INPUT_VALIDATOR.Input_Value_I(-1, keys, true);

	}

	std::cout << "Input BPM ";
	BPM = INPUT_VALIDATOR.Input_Value_I(0, 10000, true);

	std::cout << "Input Snap (1/X) ";
	snap = INPUT_VALIDATOR.Input_Value_I(0, 10000, true);

	std::cout << "Input Offset (ms) ";
	offset = INPUT_VALIDATOR.Input_Value_I(0, 10000, true);*/

	//Parameter Testing Template <For quick testing>

	keys = 18;
	numberOfGenerations = 20;
	anchor_limit = 2;
	numberOfNotes = { 8,4 };
	BPM = 146;
	snap = 4;
	offset = 53463;

	//Function to Generate Chart
	createChart(fullChartVector, numberOfGenerations, numberOfNotes, keys, anchor_limit);
	
	//Prints the chart
	visualizer(fullChartVector, numberOfGenerations, keys);

	std::cout << std::endl << "[Generating Chart]" << std::endl;

	for (int x = 0; x < numberOfGenerations; x++) {
		for (int y = 0; y < keys; y++) {
			if (fullChartVector[x][y] == true) {
				//y+1 since compiler uses 1 for first column
				COMPILER.Compiler_NN(keys, y+1, offset + ((x * (60000.0 / BPM)) / snap));
			}
		}
	}

	std::cin >> pause;

}

//Unused Stuff

//Vector Functions
//std::vector<int> uniqueVector(std::vector<int> uniquedVector);
//std::vector<int> joinVector(std::vector<int> firstVector, std::vector<int> secondVector);
//int selfMultiplyVector(std::vector<int> multiplyVector);

////Takes the Vector and returns only unique values in it
////Input: Vector to unique
////Output: Unique Vector
//std::vector<int> uniqueVector(std::vector<int> uniquedVector)
//{
//
//	unsigned int uniquedVectorSize = uniquedVector.size();
//	std::vector<int> newVector;
//
//	for (unsigned int x = 0; x < uniquedVectorSize; x++) {
//
//		if (std::count(std::begin(uniquedVector), std::begin(uniquedVector) + x, uniquedVector[x]) == 1) {
//
//			newVector.push_back(uniquedVector[x]);
//
//		}
//
//	}
//
//	return std::vector<int>();
//}
//
////Takes 2 Vectors and joins them
////Input: Vectors to join
////Output: Joint Vector
//std::vector<int> joinVector(std::vector<int> firstVector, std::vector<int> secondVector)
//{
//
//	unsigned int firstVectorSize = firstVector.size();
//
//	for (unsigned int x = 0; x < firstVectorSize; x++) {
//
//		secondVector.push_back(firstVector[x]);
//
//	}
//
//	return secondVector;
//
//}
//
//int selfMultiplyVector(std::vector<int> multiplyVector)
//{
//	unsigned int multiplyVectorSize = multiplyVector.size();
//	int result = 1;
//
//	for (unsigned int x = 0; x < multiplyVectorSize; x++) {
//
//		result *= multiplyVector[x];
//
//	}
//
//	return result;
//}
