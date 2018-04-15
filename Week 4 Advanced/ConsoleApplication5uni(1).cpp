//References:
//Source: 210CT - Week 3 Advanced task code
//Author: Kristiyan Stoyanov
//Source: 210CT - Week 4 Lecture slides: Quick Sort pseudo-code
//Author: Diana Hintea

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>

using namespace std;

void ColourMatrix() {
	//Number of rows:
	int n;
	cout << "Insert number of rows: ";
	cin >> n;
	//Number of columns:
	int m;
	cout << "Insert number of columns: ";
	cin >> m;

	//Create random device
	random_device rnd_device;
	//Specify the engine and distribution
	mt19937 mersenne_engine(rnd_device());
	uniform_int_distribution<int> dist(1, 9);

	//Assign an automatic value to the variable which is taking data based on the random factor from the mersenne engine of the int distrubtion
	auto gen = bind(dist, mersenne_engine);
	
	vector<int> digits(m);
	generate(begin(digits), end(digits), gen);

	//vector<vector<int>> matrix(n, digits);
	vector<vector<int>> mat;

	//Print the 2D matrix
	for (int i = 0; i < n; i++) {
		cout << "\n";
		//generate(begin(digits), end(digits), gen);
		shuffle(begin(digits), end(digits), mersenne_engine);
		mat.push_back(digits);
		for (int j = 0; j < m; j++) {
			cout << mat[i][j] << " ";
		}
	}

	cout << "\n";
	//Locating all different sets
	vector<int> setCollection;
	bool distinguished = false;
	int setCounter;
	int scCopy;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (setCollection.empty()) {
				setCollection.push_back(mat[i][j]);
				setCounter = 0;
			}
			else {
				scCopy = 0;
				while (scCopy <= setCounter) {
					if (setCollection[scCopy] != mat[i][j]) {
						distinguished = true;
					}
					else {
						distinguished = false;
						break;
					}
					scCopy++;
				}

				if (distinguished) {
					setCollection.push_back(mat[i][j]);
					setCounter += 1;
				}
			}
		}
	}

	cout << "\n";
	cout << "Sets found: ";
	for (int i = 0; i < setCollection.size(); i++) {
		cout << setCollection[i] << " ";
	}

	vector<vector<int>> setSizes(n, vector<int>(m));
	int largestSetSize = 0;
	int largestSetId;

	//Populate the matrix with sizes of 1 for each found set element
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			setSizes[i][j] = 1;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i > 0 && mat[i - 1][j] == mat[i][j]) {
				setSizes[i][j] = setSizes[i - 1][j] + 1;
				if (setSizes[i][j] > largestSetSize) {
					largestSetSize = setSizes[i][j];
					largestSetId = mat[i][j];
				}

			}
			if (j > 0 && mat[i][j - 1] == mat[i][j]) {
				setSizes[i][j] = setSizes[i][j - 1] + 1;
				if (setSizes[i][j] > largestSetSize) {
					largestSetSize = setSizes[i][j];
					largestSetId = mat[i][j];
				}
			}
		}
	}

	cout << "\n";
	for (int i = 0; i < n; i++) {
		cout << "\n";
		for (int j = 0; j < m; j++) {
			cout << "|" << setSizes[i][j] << "|";
		}
	}
	cout << "\n";
	cout << "Largest set size is " << largestSetSize << " of the number " << largestSetId << "\n";

}

vector<int> QuickSort(vector<int> quickVector) {

	int pivot;
	random_device rnd_device;

	vector<int> lesserPortion;
	vector<int> higherPortion;

	if (quickVector.size() <= 1) {
		return quickVector;
	}
	else {
		uniform_int_distribution<int> pivotDist(0, quickVector.size() - 1);
		pivot = pivotDist(rnd_device);
		//pivot = 0;
	}

	for (int i = 0; i < quickVector.size(); i++) {
		if (quickVector[i] < pivot) {
			lesserPortion.push_back(quickVector[i]);
		}
		else {
			higherPortion.push_back(quickVector[i]);
		}
	}

	higherPortion=QuickSort(lesserPortion);
	lesserPortion=QuickSort(higherPortion);
	lesserPortion.push_back(pivot);
	for (int i = 0; i < higherPortion.size(); i++) {
		lesserPortion.push_back(higherPortion[i]);
	}
	cout << "\n" << pivot << "\n";
	return lesserPortion;
}

vector<int> AdQuickSort(vector<int> quickVector, int mth, int &val) {

	int pivot;
	random_device rnd_device;

	vector<int> lesserPortion;
	vector<int> higherPortion;

	if (quickVector.size() <= 1) {
		return quickVector;
	}
	else {
		uniform_int_distribution<int> pivotDist(0, quickVector.size() - 1);
		pivot = pivotDist(rnd_device);
		//pivot = 0;
	}

	for (int i = 0; i < quickVector.size(); i++) {
		if (quickVector[i] < quickVector[pivot]) {
			lesserPortion.push_back(quickVector[i]);
		}
		else if (quickVector[i] > quickVector[pivot]) {
			higherPortion.push_back(quickVector[i]);
		}
	}

	cout << "\n" << pivot << "\n";

	if (lesserPortion.size() + 1 >= mth) {
		return AdQuickSort(lesserPortion, mth, val);
	}
	else if (lesserPortion.size()<= mth) {
		return AdQuickSort(higherPortion, mth - lesserPortion.size() - 1, val);
	}
	else {// pivot
		val = quickVector[pivot];
		vector<int> ret;
		return ret;
	}
}

int TestQuickSort() {
	vector<int> testVector;
	int reference = 0;
	int m;
	cout << "Specify value for m: ";
	cin >> m;

	for (int i = 1; i < 9; i++) {
		testVector.push_back(i);
	}

	AdQuickSort(testVector, m, reference);
	cout << "m is: "<< m << "\n";
	for (int i = 0; i < testVector.size(); i++) {
		cout << testVector[i] << " ";
	}
	return m;
}

void QuickSortExcercise() {

	random_device rnd_device;
	mt19937 mersenne_engine(rnd_device());
	uniform_int_distribution<int> dist(1, 9);

	auto gen = bind(dist, mersenne_engine);

	//Specify length of vector
	int n;
	cout << "Insert length for the vector: ";
	cin >> n;

	//Specify element to track within the vector
	int m;
	cout << "Insert mth smallest elemet of the vector: ";
	cin >> m;

	vector<int> quickVector (n);

	generate(begin(quickVector), end(quickVector), gen);

	cout << "\n";
	cout << "\n";
	cout << "Vector before sorting: ";
	for (int i = 0; i < n; i++) {
		cout << quickVector[i] << " ";
	}
	cout << "\n";

	bool sorted = false;
	vector<int> sortedVector;

	//Perform sorting algorithm
	QuickSort(quickVector);
	if (sortedVector.empty()) {
		sortedVector.reserve(quickVector.size());
	}
	else {
		sortedVector.reserve(sortedVector.size() + quickVector.size());
	}
	sortedVector.insert(sortedVector.end(), quickVector.begin(), quickVector.end());

	cout << "Vector after sorting: ";
	for (int i = 0; i < sortedVector.size(); i++) {
		cout << sortedVector[i] << " ";
	}
	cout << "\n";

	int smallestElement = 10;
	vector<bool>unviable (n);
	for (int i = 0; i < sortedVector.size(); i++) {
		unviable[i] = false;
	}
	int mc = 0;
	while (mc < m) {
		smallestElement = 10;
		for (int i = 0; i < sortedVector.size(); i++) {
			if (unviable[i] == false && sortedVector[i] < smallestElement) {
				smallestElement = sortedVector[i];
			}
		}
		for (int i = 0; i < sortedVector.size(); i++) {
			if (sortedVector[i] == smallestElement) {
				unviable[i] = true;
			}
		}
		mc++;
	}

	cout << m << "th smallest element is " << smallestElement << "\n";
}


int main()
{
	//ColourMatrix();
	//AdaptedQuickSort();
	TestQuickSort();
	system("pause");
    return 0;
}

