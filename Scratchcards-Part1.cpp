#include <iostream>
#include <unordered_set>
#include <fstream>
#include <string>

using namespace std;

int NumberOfSimilarNumbers(const unordered_set<string>& obtainedNumbers, const unordered_set<string>& winningNumbers);
void FindNextNumberAndInsertIntoList(unordered_set<string>& pointsList, int& currentPosition, const string& line, const unordered_set<char> numberSet);

int main() {
	fstream file;
	string line;

	int pointsTotal = 0;
	unordered_set<char> numbers = { '0', '1', '2', '3', '4' , '5', '6', '7', '8', '9' };

	file.open("../../../input.txt", ios::in);

	if (file.is_open()) {
		while (getline(file, line)) {
			//cout << "-----------------------new round---------------------" << endl;

			//create the set of winning numbers
			unordered_set<string> winningNumbers; 
			int currentPosition = line.find(':', 0); //starting location

			while (line[currentPosition] != '|') {
				FindNextNumberAndInsertIntoList(winningNumbers, currentPosition, line, numbers);
				currentPosition++;
			}
			
			/*for (auto ele : winningNumbers) {
				cout << ele << endl;
			}*/
			
			//cout << "||||||||||||||||||||||||" << endl;

			//create the set of obtainedNumbers
			unordered_set<string> obtainedNumbers;
			currentPosition++;

			while (currentPosition < line.length()) {
				FindNextNumberAndInsertIntoList(obtainedNumbers, currentPosition, line, numbers);
				currentPosition++;
			}

			/*for (auto ele : obtainedNumbers) {
				cout << ele << endl;
			}*/

			//compare winning numbers to search through if we have any in obtianed numbers
			int numberOfSimilarNums = NumberOfSimilarNumbers(obtainedNumbers, winningNumbers);

			int pointsThisCard = 0;

			if (numberOfSimilarNums >= 1) {
				pointsThisCard = 1; //starting point
				numberOfSimilarNums--;
			}

			//if obtained, set a int, multiply by that many times.
			for (int i = 0; i < numberOfSimilarNums; i++) {
				pointsThisCard *= 2;
			}
			
			//cout << pointsThisCard << " scored this ticket" << endl;

			pointsTotal += pointsThisCard;
		}
		
		cout << "---------------------------TOTAL---------------------------" << endl;
		cout << pointsTotal << endl;
	}
	else {
		cout << "file had error" << endl;
	}
}

void FindNextNumberAndInsertIntoList(unordered_set<string>& pointsList, int& currentPosition, const string& line, const unordered_set<char> numberSet) {
	if (numberSet.find(line[currentPosition]) != numberSet.end()) {
		string num = "";
		//we find a number
		num += line[currentPosition];

		//find all numbers until next space
		currentPosition++;
		while (numberSet.find(line[currentPosition]) != numberSet.end()) {
			num += line[currentPosition];
			currentPosition++;
		}
		pointsList.insert(num);
	}
}

int NumberOfSimilarNumbers(const unordered_set<string>& obtainedNumbers, const unordered_set<string>& winningNumbers) {
	int NumberOfSimilarNumbers = 0;

	for (string number : obtainedNumbers) {
		if (winningNumbers.find(number) != winningNumbers.end()) {
			NumberOfSimilarNumbers++;
		}
	}

	//cout << NumberOfSimilarNumbers << " SIMILAR" << endl;
	return NumberOfSimilarNumbers;
}