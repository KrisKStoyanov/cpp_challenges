//References:
//Source: http://www.cplusplus.com/forum/beginner/21595/
//Author: jRaskell

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string MirrorString(string usedString) {
	string inverseString;
	int sz = usedString.size();
	for (int i = sz; i >= 0; i--) {
		inverseString += usedString[i];
	}
	cout << inverseString << " ";
	return inverseString;
}

void ObtainInput() {
	int n;
	cout << "Insert number of words for insertion: ";
	while (!(cin >> n) || n <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}

	vector<string> words(n);
	string word;

	for (int i = 0; i < n; i++) {
		cout << "Insert word to data collection: ";
		cin >> word;
		words[i] = word;
	}
	for (int i = 0; i < n; i++) {
		MirrorString(words[i]);
	}
}

bool IntComparison(int i1, int i2) {
	if (i1 == i2) {
		return true;
	}
	return false;
}

bool LinearSearch() {
	int a[6];
	int target;
	for (int i = 0; i < 6; i++) {
		cout << "Insert element in array: ";
		while (!(cin >> a[i]) || a[i] <= 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}
	}
	cout << "Specify target: ";
	cin >> target;
	for (int i = 0; i < 6; i++) {
		if (IntComparison(a[i], target)) {
			cout << "Found \n";
			return true;
		}
	}
	cout << "Not found \n";
	return false;
}

class Cube {
public:
	string colour;
	int length;
	bool used = false;

	void Set_properties(string inputColour, int inputLength) {
		colour = inputColour;
		length = inputLength;
	}

	void use() {
		used = true;
	}
};

int CubeTower() {

	int numOfCubes;
	int maxTowerHeight = 0;

	string colour;
	int length;

	//Check if the input for the number of cubes specified is positive or matches the variable type
	cout << "Enter a positive value for specifying number of cubes to use: ";
	while (!(cin >> numOfCubes) || numOfCubes <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}
	cout << "\n";

	//Collection of all cubes:
	vector<Cube> cubes(numOfCubes);

	//Begin property assignment for each individual cube
	for (int i = 0; i < cubes.size(); i++) {
		cout << "Enter colour for cube: ";
		//Input validation:
		while (!(cin >> colour) || (colour != "red" && colour != "blue" && colour != "yellow" && colour != "white" && colour != "black" && colour != "pink" && colour != "purple" && colour != "green" && colour != "teal" &&
			colour != "brown" && colour != "orange" && colour != "cyan" && colour != "violet" && colour != "indigo" && colour != "grey")) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}
		cout << "Enter edge length for cube: ";
		while (!(cin >> length)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}

		cubes[i].colour = colour;
		cubes[i].length = length;
		cout << "\n";
	}

	//Variables used to compare cube properties for estimating usability:
	int maxCubeEdgeLength = 0;
	int lastCubeLength = 0;
	string lastUsedColour = "";

	//Variable for checking usability of remaining cubes within the construction loop
	bool remainingUnusable = false;

	//Variable for tracking how many usable cubes are left from the collection
	int availableCubes = cubes.size();

	//Attempt to build upon the tower until no available cubes are left or the remaining are unusable based on the properties of the last placed cube
	while (!remainingUnusable || availableCubes == 0)
	{
		//Find the longest edge length for the currently available cubes
		maxCubeEdgeLength = 0;
		for (int i = 0; i < cubes.size(); i++) {
			if (cubes[i].length > maxCubeEdgeLength && !cubes[i].used) {
				maxCubeEdgeLength = cubes[i].length;
			}
		}

		//Find the cube with edge length equal to the highest edge length
		for (int i = 0; i < cubes.size(); i++) {
			if (cubes[i].length == maxCubeEdgeLength && !cubes[i].used && cubes[i].colour != lastUsedColour) {
				cubes[i].use();
				lastUsedColour = cubes[i].colour;
				lastCubeLength = cubes[i].length;
				maxTowerHeight += cubes[i].length;
				availableCubes -= 1;
			}
		}

		//Check if there are any usable cubes left
		if (availableCubes > 0) {
			for (int i = 0; i < cubes.size(); i++) {
				if (!cubes[i].used) {
					if (cubes[i].length < lastCubeLength && cubes[i].colour != lastUsedColour) {
						remainingUnusable = false;
						break;
					}
					else {
						remainingUnusable = true;
					}
				}
				else {
					remainingUnusable = true;
				}
			}
		}
	}
	

	//Print calculated maximum tower height
	cout << "Maximum tower height: " << maxTowerHeight << "\n";
	return maxTowerHeight;
}

int main()
{
	//ObtainInput();
	//LinearSearch();
	CubeTower();
	system("pause");
    return 0;
}

