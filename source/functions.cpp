#include "functions.h"

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

			pushBackNote = rand() % keys;

			if (std::count(std::begin(chordList), std::end(chordList), pushBackNote) != 0 || std::count(std::begin(avoid), std::end(avoid), pushBackNote) != 0) {

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
void createChart(std::vector< std::vector<bool> >& fullChartVector, int numberOfGenerations, std::vector<int> numberOfNotes, int keys, int checkRange, int checkThreshold, int closestNeighbour)
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
		if (x > checkRange) {

			//We are cycling through all keys
			for (int note = 0; note < keys; note++) {

				bool avoid_flag = false;

				int checkThresholdCounter = 0;
				//This cycles through all the items in checkRange
				for (int y = 0; y < checkRange; y++) {

					if (fullChartVector[x - 2 - y][note] == true) {
						checkThresholdCounter += 1;
					}

				}

				//If the column does exceed the checkThreshold counter, we add into the avoid
				if (checkThresholdCounter > checkThreshold) {

					avoid_flag = true;

				}

				//Closest Neighbour will start from 1
				for (int y = 0; y < closestNeighbour; y++) {

					if (fullChartVector[x - (y + 2)][note] == true) {

						avoid_flag = true;

					}

				}


				if (avoid_flag == true) {

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