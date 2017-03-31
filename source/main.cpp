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

void visualizer(std::vector< std::vector<bool> > &fullChartVector, int rows, int keys);
std::vector<int> generateChord(int numberOfNotes, int keys, std::vector<int> &avoid);

void createChart(std::vector< std::vector<bool> > &fullChartVector, int numberOfGenerations, int numberOfNotes, int keys);

//Debug Functions
void displayVector(std::vector<int> displayedVector);
void displayVector(std::vector<bool> displayedVector);

const bool DEBUG = true;

int main() {

	int pause;

	int	densityLevel;
	int bracketDifficultyLevel;

	std::vector<int> densityLevelList = {
		1111,2111,2121,
		2221,2222,3222,
		3232,3332,3333,
		4333,4343
	};

	//Generates the Chart
	std::vector< std::vector<bool> > fullChartVector;
	int keys;
	int numberOfGenerations;
	int numberOfNotes;

	//Parameters
	numberOfGenerations = 100;
	numberOfNotes = 3;
	keys = 7;

	//Function to Generate Chart
	createChart(fullChartVector, numberOfGenerations, numberOfNotes, keys);
	
	//Prints the chart
	visualizer(fullChartVector, numberOfGenerations, keys);

	std::cin >> pause;
}

//Prints the whole chart vector
//Input: (BVectorVector) The full chart Vector, (Int) Number of Generations, (Int) Number of Keys
void visualizer(std::vector< std::vector<bool> > &fullChartVector, int numberOfGenerations, int keys)
{

	std::cout << "[Visualizer]" << std::endl;

	for (int x = (numberOfGenerations - 1); x > -1; x--) {

		for (int y = 0; y < keys; y++) {

			if (fullChartVector[x][y] == true) {

				//Means there is no note
				std::cout << "_";

			}
			else {

				//Means there is a note
				std::cout << "O";
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

	std::cout << "[Generate Chord]" << std::endl;

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

				std::cout << "Threshold: " << threshold << std::endl;
				threshold += 1;

				if (threshold > 100) {
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
void createChart(std::vector< std::vector<bool> >& fullChartVector, int numberOfGenerations, int numberOfNotes, int keys)
{

	std::vector<int> generateChordVector;
	std::vector<int> avoidVector = {};

	for (int x = 0; x < numberOfGenerations; x++) {

		std::vector<bool> rowVector;

		//Testing generateChord
		generateChordVector = generateChord(numberOfNotes, keys, avoidVector);

		std::cout << "[Generate Chord Vector]" << std::endl;
		displayVector(generateChordVector);

		//Sets Current chord vector to be used for avoid later
		avoidVector = generateChordVector;

		for (int y = 0; y < keys; y++) {

			//If the key here isn't in the list, we push back a false, vice versa
			if (std::count(std::begin(generateChordVector), std::end(generateChordVector), y) != 0) {
				rowVector.push_back(false);

				std::cout << "[Row Vector]" << std::endl;
				displayVector(rowVector);

			}
			else {
				rowVector.push_back(true);

				std::cout << "[Row Vector]" << std::endl;
				displayVector(rowVector);

			}

		}

		fullChartVector.push_back(rowVector);

	}

}

//Displays the Vector <Debug Function>
//Input: (IVector) The Vector to display
void displayVector(std::vector<int> displayedVector)
{

	if (DEBUG == true) {

		unsigned int displayedVectorSize = displayedVector.size();

		std::cout << "[DEBUG] Display Vector: ";

		for (unsigned int x = 0; x < displayedVectorSize; x++) {

			std::cout << displayedVector[x] << ",";

		}

		std::cout << std::endl;

	}

}

//Displays the Vector <Debug Function>
//Input: (IVector) The Vector to display
void displayVector(std::vector<bool> displayedVector)
{

	if (DEBUG == true) {

		unsigned int displayedVectorSize = displayedVector.size();

		std::cout << "[DEBUG] Display Vector: ";

		for (unsigned int x = 0; x < displayedVectorSize; x++) {

			std::cout << displayedVector[x] << ",";

		}

		std::cout << std::endl;

	}
}