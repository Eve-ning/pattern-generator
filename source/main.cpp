/*

	Amount of keys
	Density
	Difficulty

	Density:
	
		Taking 4 Samples of note count per chord

		Minimum: 1111
		Maximum: 4343

		Density Level

		1)	1111
		2)	2111
		3)	2121
		4)	2221
		5)	2222
		6)	3222
		7)	3232
		8)	3332
		9)	3333
		10)	4333
		11)	4343	

	Bracket Difficulty:

		Difficulty Level

		This is represented as the fingers
		0 1 2 3 4 5 6 7 8 9

		Note: Default center key to 5 instead of 4

		1)	35 4
		1)	68 7
		2)	34 2
		2)	78 9	
		3)	24 3
		3)	79 8

	Anchor Difficulty:

		Difficulty Level

		We count by amount of repetitions/anchor length

		1)	  2
		2)	  3
		3)	  4
		4)	  5
		MAX)  6+

*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

void visualizer(std::vector< std::vector<bool> > &fullChartVector, int rows, int keys);

std::vector<int> generateChord(int numberOfNotes, int keys, std::vector<int> &avoid);

void createChart(std::vector< std::vector<bool> > &fullChartVector, int numberOfGenerations, std::vector<int> numberOfNotes, int keys, int anchor_limit);

//Vector Functions
//std::vector<int> uniqueVector(std::vector<int> uniquedVector);
//std::vector<int> joinVector(std::vector<int> firstVector, std::vector<int> secondVector);
//int selfMultiplyVector(std::vector<int> multiplyVector);

//Just to print things
template<class TYPE>
void printDEBUG(std::string message, TYPE parameter);

//Debug Functions
void displayVector(std::vector<int> displayedVector);
void displayVector(std::vector<bool> displayedVector);

int main() {

	int pause;

	//Generates the Chart
	std::vector< std::vector<bool> > fullChartVector;
	int keys;
	int numberOfGenerations;
	int anchor_limit;
	std::vector<int> numberOfNotes;

	//Parameters
	numberOfGenerations = 100;
	numberOfNotes = { 20,10 };
	keys = 40;
	anchor_limit = 2;

	//Function to Generate Chart
	createChart(fullChartVector, numberOfGenerations, numberOfNotes, keys, anchor_limit);
	
	//Prints the chart
	visualizer(fullChartVector, numberOfGenerations, keys);

	std::cin >> pause;
}

//Prints the whole chart vector
//Input: (BVectorVector) The full chart Vector, (Int) Number of Generations, (Int) Number of Keys
void visualizer(std::vector< std::vector<bool> > &fullChartVector, int numberOfGenerations, int keys)
{

	for (int x = (numberOfGenerations - 1); x > -1; x--) {

		for (int y = 0; y < keys; y++) {

			if (fullChartVector[x][y] == true) {

				//Means there is no note
				std::cout << "O ";

			}
			else {

				//Means there is a note
				std::cout << "_ ";
			}

		}

		std::cout << std::endl;
	}
}

//Generates a chord and avoids a list if given
//Input: (Int) Number of Notes, (Int) Number of Keys, (IVector) List to avoid
//Output: (IVector) The chord generated
std::vector<int> generateChord(int numberOfNotes, int keys, std::vector<int> &avoid)
{

	std::vector<int> chordList = {};
	bool uniqueFlag;

	for (int x = 0; x < numberOfNotes; x++) {

		//If the program can't find a suitable number in 100 tries it'll skip the note
		int threshold = 0;

		//Set uniqueFlag to false at the start of every generation
		uniqueFlag = false;

		//Create a flag to make sure the generated note is unique
		while (uniqueFlag == false) {
			
			//We create a variable here to check if the note generated is in the list already
			int pushBackNote;

			pushBackNote = rand()%keys;

			if (std::count(std::begin(chordList), std::end(chordList), pushBackNote) != 0 || std::count(std::begin(avoid), std::end(avoid), pushBackNote) != 0 ){

				threshold += 1;

				if (threshold > 500) {
					uniqueFlag = true;
				}

				continue;
			}
			else {
				chordList.push_back(pushBackNote);
				//Set to true to exit while loop
				uniqueFlag = true;
			}

		}
	}

	return chordList;
}

//Creates the chart
//Input: (BVectorVector) Full Chart Vector, (Int) Number of Generations, (Int) Number of Notes, (Int) Number of Keys
void createChart(std::vector< std::vector<bool> >& fullChartVector, int numberOfGenerations, std::vector<int> numberOfNotes, int keys, int anchor_limit)
{

	std::vector<int> generateChordVector;
	std::vector<int> avoidVector = {};

	unsigned int numberOfNotesSize = numberOfNotes.size();

	for (int x = 0; x < numberOfGenerations; x++) {

		//We reset Avoid Vector every generation
		avoidVector = {};

		std::cout << "[Generating Column " << x << "]" << std::endl;

		//We Set up what to avoid first

		//Sets Current chord vector to be used for avoid later
		//Condition since first chord doesn't avoid anything
		if (x > 0) {

			for (int note = 0; note < keys; note++) {

				//We refer to the previous chord as (x - 1)
				if (fullChartVector[x - 1][note] == true) {

					//We push back if there is a true on the previous column
					avoidVector.push_back(note);

				}

			}
		}

		//The least amount of already generations for this to trigger
		if (x >= (anchor_limit * 2)) {	

			//We are cycling through all keys
			for (int note = 0; note < keys; note++) {

				int validate = 1;

				//This cycles through 0 2 4 and so on, the even ones
				for (int y = 0; y < anchor_limit; y++) {

					int referenceIndex;

					//Reference index is the index of the chart we are going to refer to for anchors
					referenceIndex = x - (2 * (y + 1));

					//If there isn't a note it's going to return 0 and validate will permanently turn 0
					validate *= (int) fullChartVector[referenceIndex][note];

				}

				if (validate == 1) {

					avoidVector.push_back(note);

				}

			}

		}

		unsigned int numberOfNotesSize = numberOfNotes.size();

		//If the numberOfNotes is a list, we will cycle through that
		generateChordVector = generateChord(numberOfNotes[x % numberOfNotesSize], keys, avoidVector);

		std::vector<bool> rowVector;

		for (int y = 0; y < keys; y++) {

			//If the key here isn't in the list, we push back a false, vice versa
			if (std::count(std::begin(generateChordVector), std::end(generateChordVector), y) != 0) {
				rowVector.push_back(true);

			}
			else {
				rowVector.push_back(false);

			}

		}

		fullChartVector.push_back(rowVector);

	}
	
}

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
