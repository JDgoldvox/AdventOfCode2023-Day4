#include <iostream>
#include <unordered_set>
#include <fstream>
#include <string>

using namespace std;

string FindLine(const int& targetLineNumber);
int ScratchTheCard(const unordered_set<char>& numbers, const string& line, const int& linesInTxt);
int NumberOfSimilarNumbers(const unordered_set<string>& obtainedNumbers, const unordered_set<string>& winningNumbers);
void FindNextNumberAndInsertIntoList(unordered_set<string>& pointsList, int& currentPosition, const string& line, const unordered_set<char> numberSet);

int main() {
	fstream file;
	string line;

	int totalScratchCards = 0;
	unordered_set<char> numbers = { '0', '1', '2', '3', '4' , '5', '6', '7', '8', '9' };

	file.open("../../../input.txt", ios::in);

	if (file.is_open()) {

		int linesInTxt = 0;

		while (getline(file, line)) {
			linesInTxt++;
		}

		//reset getLine items
		file.clear();  // Clear EOF flag
		file.seekg(0, ios::beg);  // Move pointer back to the beginning of the file

		int currentCardNum = 1;
		while (getline(file, line)) {

			cout << endl << currentCardNum << "/" << linesInTxt << endl;
			int num = 0;
			num += ScratchTheCard(numbers, line, linesInTxt);
			totalScratchCards += num;
			currentCardNum++;
		}

		cout << "---------------------------TOTAL---------------------------" << endl;
		cout << totalScratchCards << endl;
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

	return NumberOfSimilarNumbers;
}

int FindCardNumber(const string& line, const unordered_set<char>& numbers) {
	int currentPosition = 0;

	string numberAsString = "";

	//find the card number
	while (line[currentPosition] != ':') {

		if (numbers.find(line[currentPosition]) != numbers.end()) {
			numberAsString += line[currentPosition];
		}

		currentPosition++;
	}

	//convert to int
	return stoi(numberAsString);
}

string FindLine(const int& targetLineNumber) {
	//create new file stream
	fstream file;
	string line;

	file.open("../../../input.txt", ios::in);

	int currentLineNumber = 0;

	if (file.is_open()) {
		//loop through all lines until targetLineNumber is found
		while (getline(file, line)) {
			currentLineNumber++;

			if (currentLineNumber == targetLineNumber) {
				return line;
			}
		}
	}
	else {
		cout << "file not open in FindLine()" << endl;
	}

	file.close();
}

int ScratchTheCard(const unordered_set<char>& numbers, const string& line, const int& linesInTxt) {
	int numberOfScratchCards = 1; //count this card

	//create the set of winning numbers
	unordered_set<string> winningNumbers;
	int currentPosition = line.find(':', 0); //starting location

	while (line[currentPosition] != '|') {
		FindNextNumberAndInsertIntoList(winningNumbers, currentPosition, line, numbers);
		currentPosition++;
	}

	//create the set of obtainedNumbers
	unordered_set<string> obtainedNumbers;
	currentPosition++;

	while (currentPosition < line.length()) {
		FindNextNumberAndInsertIntoList(obtainedNumbers, currentPosition, line, numbers);
		currentPosition++;
	}

	//compare winning numbers to search through if we have any in obtianed numbers
	int numberOfSimilarNums = NumberOfSimilarNumbers(obtainedNumbers, winningNumbers);
	int currentCardNum = FindCardNumber(line, numbers);

	cout << numberOfSimilarNums;

	//scratch the cards that this card has won
	string newLine;
	if (numberOfSimilarNums == 0) {
		return numberOfScratchCards;
	}

	int maxRangeForCards = numberOfSimilarNums + currentCardNum;
	for (int i = currentCardNum + 1; i <= maxRangeForCards; i++) {
		//check if the i goes over total lines
		if (i < linesInTxt) {
			newLine = FindLine(i);
			numberOfScratchCards += ScratchTheCard(numbers, newLine, linesInTxt);
		}
	}

	return numberOfScratchCards;
}