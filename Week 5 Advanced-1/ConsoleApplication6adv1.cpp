//References:
//Source: 210CT - Week 4 Advanced Task N#1 code
//Author: Kristiyan Stoyanov

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>

using namespace std;

vector<int> resetVector(vector<int> usedVector) {
	while (!usedVector.empty())
	{
		usedVector.pop_back();
	}
	return usedVector;
}

vector<bool> resetPosition(vector<bool> usedVector) {
	for (int i = 0; i < usedVector.size(); i++) {
		usedVector[i] = false;
	}
	return usedVector;
}

void DiagonalSumMatrix() {

	//Matrix size
	int mSize;
	cout << "Specify size of the matrix: ";
	//Input validation for matrix size declaration
	while (!(cin >> mSize) || mSize <= 0)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}

	//Number of integer values a sum is composed 
	int numDigits;
	cout << "Insert number of digits for sum: ";
	//Input validation for number of digits declaration
	while (!(cin >> numDigits) || numDigits <= 0)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}

	random_device rnd_device;
	mt19937 mersenne_engine(rnd_device());
	uniform_int_distribution<int> dist(1, 9);

	auto gen = bind(dist, mersenne_engine);

	vector<int> digits(mSize);
	generate(begin(digits), end(digits), gen);

	//Matrix declaration
	vector<vector<int>> mat;

	//Collection of integer sums from viable diagonals
	vector<int> diagonalSum;

	//Default comparison initialising variable for obtaining the smallest sum of integers 
	//in a diagonal from the diagonal sum collection
	int smallestSum = mSize * 10;

	//Vector for collection integers in a diagonal
	vector<int> diagonalCol;

	//Vector for collecting sums of integers in a diagonal
	vector<int> sumCol;

	//Last saved position of loop iteration within the 2D matrix
	int savedPos;
	 
	//Print the 2D matrix as it is being established
	for (int i = 0; i < mSize; i++) {
		cout << "\n";
		//Shuffle the randomly generated values for the elements in each row of the matrix
		shuffle(begin(digits), end(digits), mersenne_engine);
		mat.push_back(digits);
		for (int j = 0; j < mSize; j++) {
			cout << mat[i][j] << " ";
		}
	}
	
	//Counter for keeping track of number of obtained digits for a calculated sum of integers in a diagonal
	int counter = 0;

	//Default sum of variables to initialise a diagonal sum with
	int sum = 0;

	//Iterative loop for collecting diagonal values
	for (int i = 0; i < mSize; i++) {
		for (int j = 0; j < mSize; j++) {

			//Reset sum and counter for each diagonal
			sum = 0;
			counter = 0;

			//Reset the vectors to which integers of a diagonal and the integers
			//used for obtaining the lowest of a sum in a diagonal are stored
			diagonalCol = resetVector(diagonalCol);
			sumCol = resetVector(sumCol);

			//Only try to gather the values of a diagonal if this is the start of the main diagonal
			//or any parralel diagonal with enough elements to calculate a sum composed of the
			//specified number of integer values (numDigits) for establishing a sum

			//Diagonals starting from the Y axis of a 2D plane
			if (i == 0) {
				if (mSize - j >= numDigits) {
					//Add all element values of a diagonal
					while (counter < mSize - j) {
						diagonalCol.push_back(mat[i + counter][j + counter]);
						counter += 1;
					}

					//Find the smallest value of an element from the diagonal
					//which hasn't been added to the collection of values for calculating this diagonal's sum
					int minValue;
					vector<bool> registeredPosition(diagonalCol.size());
					registeredPosition = resetPosition(registeredPosition);
					while (sumCol.size() < numDigits)
					{
						minValue = 10;
						for (int a = 0; a < diagonalCol.size(); a++) {
							if (diagonalCol[a] < minValue && registeredPosition[a] == false) {
								minValue = diagonalCol[a];
								savedPos = a;
							}
						}
						sumCol.push_back(minValue);
						registeredPosition[savedPos] = true;
					}

					//Add up the smallest integers into a single value which is then stored into the collection of all diagonal sums
					for (int b = 0; b < sumCol.size(); b++) {
						sum += sumCol[b];
					}
					diagonalSum.push_back(sum);
				}
			}

			//Diagonals starting from the X axis of a 2D plane
			else if (j == 0) {
				if (mSize - i >= numDigits) {
					while (counter < mSize - i)
					{
						diagonalCol.push_back(mat[i + counter][j + counter]);
						counter += 1;
					}
					int minValue;
					vector<bool> registeredPosition(diagonalCol.size());
					registeredPosition = resetPosition(registeredPosition);
					while (sumCol.size() < numDigits)
					{
						minValue = 10;
						for (int a = 0; a < diagonalCol.size(); a++) {
							if (diagonalCol[a] < minValue && registeredPosition[a] == false) {
								minValue = diagonalCol[a];
								savedPos = a;
							}
						}
						sumCol.push_back(minValue);
						registeredPosition[savedPos] = true;
					}
					for (int b = 0; b < sumCol.size(); b++) {
						sum += sumCol[b];
					}
					diagonalSum.push_back(sum);
				}
			}
		}
	}
	cout << "\n";

	//Find the smallest diagonal sum from all of the values that have been gathered 
	for (int i = 0; i < diagonalSum.size(); i++) {
		cout << diagonalSum[i] << "\n";
		if (diagonalSum[i] < smallestSum) {
			smallestSum = diagonalSum[i];
		}
	}
	cout << "Smallest sum of integers on a diagonal parralel to the main diagonal: " << smallestSum << "\n";
}


int main()
{
	DiagonalSumMatrix();
	system("pause");
	return 0;
}

