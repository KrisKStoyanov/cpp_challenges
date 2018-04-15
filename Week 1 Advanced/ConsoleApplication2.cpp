//References:
//Source: http://www.cplusplus.com/forum/beginner/21595/
//Author: jRaskell

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

string combineStrings() {
	
	string firstStr;
	string secStr;

	string endStr = "";

	cout << "Insert first string: " << "\n";
	cin >> firstStr;

	cout << "Insert second string: " << "\n";
	cin >> secStr;

	if (firstStr.size() >= secStr.size()) {
		for (int i = 0; i < firstStr.size(); i++) {
			endStr += firstStr[i];
			if (!secStr[i] == '\0') {
				endStr += secStr[i];
			}
		}
	}

	else {
		for (int i = 0; i < secStr.size(); i++) {
			if (!firstStr[i] == '\0') {
				endStr += firstStr[i];
			}
			endStr += secStr[i];
		}
	}

	cout << endStr << "\n";
	return endStr;
}

bool armstrongNumber() {
	int num;

	bool armstrong = "";

	string strDigit;
	int digitCol [3];

	cout << "Insert a number of 3 digits: ";
	cin >> num;
	string strEq = to_string(num);

	for (int i = 0; i < 3; i++) {
		strDigit = strEq[i];
		digitCol[i] = stoi(strDigit);
		cout << digitCol[i] << "\n";
	}

	if (pow(digitCol[0],strEq.size()) + pow(digitCol[1],strEq.size()) + pow(digitCol[2],strEq.size()) == num)
	{
		armstrong = true;
		cout << "Yes \n";
	}
	else
	{
		armstrong = false;
		cout << "No \n";
	}
	return armstrong;
}

unsigned long long calculateFactiorial(int x = NULL, int y = NULL) {
	int n, m;
	
	//Check if the optional values to use are predefined at the start of the method
	//and reallocate them if they do not correspond to the required conditions
	if (x == NULL) {
		n = NULL;
	}
	else {
		if (x > 0 && x < 231) {
			n = x;
		}
		else {
			cout << "Given input does not correspond to method conditions. \n";
			n = NULL;
		}
	}

	if (y == NULL) {
		m = NULL;
	}
	else {
		if (y > 0 && y < 231) {
			m = y;
		}
		else {
			cout << "Given input does not correspond to program conditions. \n";
			m = NULL;
		}
	}

	int b;
	unsigned long long factorial;

	//If there are no predefined values to the method or they do not correspond to the specific conditions attempt to gather new input for them
	if (n == NULL) {
		cout << "Insert first number with specified condition (N# > 0 & N# < 231): ";
		//Check if the input matches the requested variable type and condition and attempt to write it in memory to the declared variable (n)
		while (!(cin >> n) || n <= 0 || n >= 231)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}
	}

	if (m == NULL) {
		cout << "Insert second number with specified condition (N# > 0 & N# < 231): ";
		//Check if the input matches the requested variable type and condition and attempt to write it in memory to the declared variable (m)
		while (!(cin >> m) || m <= 0 || m >= 231)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}
	}


	b = n;
	factorial = n;

	//Calculate the factorial of the first number
	while (b > 1) {
		factorial *= (b - 1);
		b -= 1;
		cout << factorial << "\n";
	}

	//Check if the remainder from the division of the factorial of the first number by the second number is equal to 0,
	//output the result and return the calculated factorial number
	if (factorial % m == 0) {
		cout << m << " divides " << n << "!" << "\n";
	}
	else {
		cout << m << " does not divide " << n << "!" << "\n";
	}

	return factorial;
}

class Material {
public:
	string type;
	int amount;
	int value;

	void Set_properties(string inputType, int inputAmount, int inputValue) {
		type = inputType;
		amount = inputAmount;
		value = inputValue;
	}

};

int lorryLoadComposition() {
	int loadCapacity;
	cout << "Insert lorry load capacity (kg): ";
	while (!(cin >> loadCapacity))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}

	int numOfMats;
	cout << "Insert number of materials: ";
	while (!(cin >> numOfMats))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}

	cout << "\n";

	vector<Material> mats (numOfMats);

	for (int i = 0; i < mats.size(); i++) {

		string matType;
		cout << "Insert material type: ";
		while (!(cin >> matType))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}

		int matAmount;
		cout << "Insert amount of kg for specified material: ";
		while (!(cin >> matAmount))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}

		int matValue;
		cout << "Insert value per kg of specified material: ";
		while (!(cin >> matValue))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}

		Material mat;
		mat.Set_properties(matType, matAmount, matValue);
		mats[i] = mat;
		cout << "\n";
	}

	cout << "Available materials: \n";
	for (int i = 0; i < mats.size(); i++) {
		cout << "Type: " << mats[i].type << ", Amount: "<< mats[i].amount <<", Value per kg: "<< mats[i].value << "\n";
	}
	cout << "\n";

	int acquiredLoad = 0;

	int combinedLoadValue = 0;

	int highestValue = 0;
	int amountToCollect = 0;
	string highestValMat;

	vector<Material> loadedMats;
	bool amountOfMatDepleted = false;

	//Fill the lorry until the load capacity is reached or all of the materials are depleted
	while (acquiredLoad < loadCapacity || amountOfMatDepleted == true)
	{

		//Find most valuable material
		highestValue = 0;
		for (int i = 0; i < mats.size(); i++) {
			if (highestValue < mats[i].value && mats[i].amount != 0) {
				highestValue = mats[i].value;
				highestValMat = mats[i].type;
				if (mats[i].amount > loadCapacity - acquiredLoad) {
					amountToCollect = loadCapacity - acquiredLoad;
				}
				else {
					amountToCollect = mats[i].amount;
				}
			}
		}

		//Remove the amount of collected material from the last most valuable material
		for (int i = 0; i < mats.size(); i++) {
			if (mats[i].type == highestValMat) {
				mats[i].amount -= amountToCollect;
			}
		}

		//Add the most valuable material found to the lorry's loaded materials and increase the current load
		Material mostValMat;
		mostValMat.Set_properties(highestValMat, amountToCollect, highestValue);
		loadedMats.push_back(mostValMat);
		acquiredLoad += amountToCollect;

		//Check if there is more amount of materials which can be loaded
		for (int i = 0; i < mats.size(); i++) {
			if (mats[i].amount == 0) {
				amountOfMatDepleted = true;
			}
			else {
				amountOfMatDepleted = false;
				break;
			}
		}
	}

	//Calculated the maximum combined value that the lorry can carry
	for (int i = 0; i < loadedMats.size(); i++) {
		combinedLoadValue += loadedMats[i].amount * loadedMats[i].value;
	}

	cout << "Load composition value: " << combinedLoadValue << "\n";
	cout << "Lorry load composition: ";
	for (int i = 0; i < loadedMats.size(); i++) {
		if (loadedMats[i].type != loadedMats.back().type) {
			cout << loadedMats[i].amount << " kg of " << loadedMats[i].type << ", ";
		}
		else {
			cout << loadedMats[i].amount << " kg of " << loadedMats[i].type << "\n";
		}
	}

	return combinedLoadValue;
}

int main()
{
	//combineStrings();
	//armstrongNumber();
	calculateFactiorial();
	lorryLoadComposition();
	system("pause");
    return 0;
}

