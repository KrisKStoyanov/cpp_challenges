//References:
//Address: https://stackoverflow.com/questions/876901/calculating-execution-time-in-c
//Author: Ashutosh Mehra

#include "stdafx.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <time.h>

using namespace std;


void polynomialCalculus() {

	//calculate runtime
	clock_t c = clock();
	
	int d1;
	int d2;

	cout << "Insert degree for first polynomial: ";
	cin >> d1;

	cout << "Insert degree for second polynomial: ";
	cin >> d2;

	int p1[3] = { 3,1,9 };
	int p2[4] = { 2,1,2,1 };

	int resD;
	int resP[4];

	int degreeDiff;

	degreeDiff = d1 - d2;
	if (degreeDiff < 0) {
		degreeDiff *= -1;
	}

	if (d1 > d2) {
		resD = d1;
		for (int i = 0; i < degreeDiff; i++) {
			resP[i] = p1[i];
		}
		for (int i = degreeDiff; degreeDiff < 4; degreeDiff++) {
			resP[degreeDiff] = p1[degreeDiff] + p2[degreeDiff - 1];
		}
	}

	else {
		resD = d2;
		for (int i = 0; i < degreeDiff; i++) {
			resP[i] = p1[i];
		}
		resP[0] = p2[0];
		for (int i = degreeDiff; degreeDiff < 4; degreeDiff++) {
			resP[degreeDiff] = p2[degreeDiff] + p1[degreeDiff - 1];
		}
	}

	cout << "Degree of result: " << resD << "\n";
	cout << "Res = ";
	for (int i = 0; i < 4; i++) {
		cout << resP[i] << " ";
	}
	cout << "\n";
	c = clock() - c;
	cout << "Runtime Estimate (Seconds): "<< ((float)c) / CLOCKS_PER_SEC << "\n";
}

void polynomialMultiplication() {
	
	//Calculate runtime from the start of the method
	clock_t c = clock();

	int p1[3] = { 3,1,9 };
	int p2[4] = { 2,1,2,1 };

	int d1;
	int d2;
	cout << "Insert degree of first polynomial: ";
	cin >> d1;
	cout << "Insert degree of second polynomial: ";
	cin >> d2;

	int resD = d1 * d2 - 1;
	int resP[6] = { 0,0,0,0,0,0 };
	int degreeDiff;

	if (d1 > d2) {
		degreeDiff = resD - d2;
	}
	else {
		degreeDiff = resD - d1;
	}

	int s = sizeof(p1);
	int i = 0;
	int j = 0;
	
	for(int i = 0; i < 3; i ++){
		for (int j = 0; j < 4; j++) {
			resP[i + j] = resP[i + j] + p1[i] * p2[j];
		}
	}

	cout << "Degree of resulting polynomial: "<< resD << "\n";
	cout << "Res = ";
	for (int i = 0; i < resD + 1; i++) {
		cout << resP[i] << " ";
	}
	cout << "\n";
	//Print estimated time to complete the method
	c = clock() - c;
	cout << "Runtime Estimate (Seconds): " << ((float)c) / CLOCKS_PER_SEC << "\n";
}

void polynomialDerivative() {

	//Calculate runtime from the start of the method
	clock_t c = clock();

	int d1;
	int d2;

	cout << "Insert degree for first polynomial: ";
	cin >> d1;
	cout << "Insert degree for second polynomial: ";
	cin >> d2;

	int d1c = d1;
	int d2c = d2;

	int p1[3] = { 3,1,9 };
	int p2[4] = { 2,1,2,1 };

	int resD1 = d1 - 1;
	int resD2 = d2 - 1;

	int resP1[2];
	int resP2[3];

	for (int i = 0; i < 2; i++) {
		resP1[i] = p1[i] * d1c;
		d1c -= 1;
	}

	for (int i = 0; i < 3; i++) {
		resP2[i] = p2[i] * d2c;
		d2c -= 1;
	}
	cout << "Degree = " << resD1 << "\n";
	cout << "Res1 = ";
	for (int i = 0; i < 2; i++) {
		if (resP1[i] > 0) {
			cout << resP1[i] << " ";
		}
	}
	cout << "\n";
	cout << "Degree = " << resD2 << "\n";
	cout << "Res2 = ";
	for (int i = 0; i < 3; i++) {
		if (resP2[i] > 0) {
			cout << resP2[i] << " ";
		}
	}
	cout << "\n";
	//Print estimated time to complete the method
	c = clock() - c;
	cout << "Runtime Estimate (Seconds): " << ((float)c) / CLOCKS_PER_SEC << "\n";
}

void palindromeArray() {

	//Calculate runtime from the start of the method
	clock_t c = clock();

	bool palindrome;

	int mainArray[6];
	int revArray[6];
	int i = 0;
	int j = 5;
	for (i = 0; i < 6;) {
		cout << "Insert array element: ";
		cin >> mainArray[i];
		revArray[j] = mainArray[i];
		i++;
		j--;
	}
	cout << "\n";

	for (i = 0; i < 6; i++) {
		cout << mainArray[i] << " ";
	}
	cout << "\n";
	for (i = 0; i < 6; i++) {
		cout << revArray[i] << " ";
	}
	cout << "\n";
	for (int a = 0; a < 6; a++) {
		if (mainArray[a] == revArray[a]) {
			palindrome = true;
		}
		else
		{
			palindrome = false;
			break;
		}
	}
	if (palindrome) {
		cout << "Yes \n";
	}
	else
	{
		cout << "No \n";
	}
	//Print estimated time to complete the method
	c = clock() - c;
	cout << "Runtime Estimate (Seconds): " << ((float)c) / CLOCKS_PER_SEC << "\n";
}


void QueensPuzzle() {

	int m[8][8];

	int y = 0;
	int x = 0;

	//Horizontal & vertical properties:

	//Vertical Up
	int vu = 1;
	//Vertical Down
	int vd = 1;
	//Horizontal Left
	int hl = 1;
	//Horizontal Right
	int hr = 1;

	//Diagonal properties:

	//Diagonal upper left
	int dul;
	//Diagonal upper right
	int dur;
	//Diagonal down left
	int ddl;
	//Diagonal down right
	int ddr;

	//Queen counter initialised at 0 at the start
	int qc = 0;

	//Indicator of an available poisition for a new queen to be placed
	bool foundPos = false;

	//Insert 0 in each element of the board matrix 
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			m[y][x] = 0;
		}
	}

	//Check available positions to determine where the first queen can be placed on the board (matrix)
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			//Reset current position to false until proven otherwise
			foundPos = false;
			//If a queen is occupying this stop terminate the process
			if (m[y][x] == 1) {
				break;
			}

			//Check if a queen can be found horizontally, vertically and on every diagonal 
			//passing through the current position of the board (element of the matrix)
			vu = y;
			vd = 7 - y;
			hl = x;
			hr = 7 - x;


			if (hl > vu) {
				dul = vu;
			}
			else {
				dul = hl;
			}

			if (hr > vu) {
				dur = vu;
			}
			else
			{
				dur = hr;
			}

			if (hl > vd) {
				ddl = vd;
			}
			else {
				ddl = hl;
			}

			if (hr > vd) {
				ddr = vd;
			}
			else {
				ddr = hr;
			}

			//Iterate over each position of the horizontal, vertical and diagonal placements on the board (matrix)
			while (vu > 0 || vd > 0 || hr > 0 || hl > 0) {
				if (m[y - vu][x] == 1 ||
					m[y + vd][x] == 1 ||
					m[y][x - hl] == 1 ||
					m[y][x + hr] == 1 ||
					m[y - dul][x - dul] == 1 ||
					m[y - dur][x + dur] == 1 ||
					m[y + ddl][x - ddl] == 1 ||
					m[y + ddr][x + ddr] == 1)
				{
					foundPos = false;
					break;
				}
				else {
					foundPos = true;
					vu--;
					vd--;
					hl--;
					hr--;
					if (vu < 1 && vd >= 1 && hl >= 1 && hr >= 1) {
						vu = 0;
					}
					if (vd < 1 && vu >= 1 && hl >= 1 && hr >= 1) {
						vd = 0;
					}
					if (hl < 1 && hr >= 1 && vu >= 1 && vd >= 1) {
						hl = 0;
					}
					if (hr < 1 && hl >= 1 && vu >= 1 && vd >= 1) {
						hr = 0;
					}
					dul--;
					dur--;
					ddl--;
					ddr--;
					if (hl > vd) {
						ddl = vd;
					}
					else {
						ddl = hl;
					}

					if (hr > vd) {
						ddr = vd;
					}
					else {
						ddr = hr;
					}
				}
			}
			//If the current position is found to be available place a queen there
			if (foundPos == true) {
				m[y][x] = 1;
				break;
			}
		}
	}

	//Check how many queens are currently on the board (matrix)
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			if (m[y][x] == 1) {
				qc += 1;
			}
		}
	}

	int x2 = 0;
	int y2 = 0;

	//If the placed queens are less than 8 backtrack to the last queen position and switch its position to the next available location on the board
	while (qc < 8) {
		bool switched = false;
		bool foundNext = false;
		qc = 0;

		//Comment/uncomment line below to display board index iterations
		//cout << "X: " << x << " X2: " << x2 << " == Y: " << y << " Y2: " << y2;

		//First Step - Find last valid queen position and remove it while saving the data for the next places on the board
		for (y = 7; y >= 0; y--) {
			for (x = 0; x < 8; x++) {
				if (m[y][x] == 1 && x < 7 && switched == false) {
					m[y][x] = 0;
					x2 = x + 1;
					y2 = y;
					switched = true;
				}
				else if (switched == false) {
					m[y][x] = 0;
				}
			}
		}

		//Second Step - Start looking for next valid queen position after last queen/s position is removed
		for (x = x2; x < 8; x++) {
			foundPos = false;
			vu = y2;
			vd = 7 - y2;
			hl = x;
			hr = 7 - x;

			if (hl > vu) {
				dul = vu;
			}
			else {
				dul = hl;
			}

			if (hr > vu) {
				dur = vu;
			}
			else
			{
				dur = hr;
			}

			if (hl > vd) {
				ddl = vd;
			}
			else {
				ddl = hl;
			}

			if (hr > vd) {
				ddr = vd;
			}
			else {
				ddr = hr;
			}

			while (vu > 0 || vd > 0 || hr > 0 || hl > 0) {
				if (m[y2 - vu][x] == 1 ||
					m[y2 + vd][x] == 1 ||
					m[y2][x - hl] == 1 ||
					m[y2][x + hr] == 1 ||
					m[y2 - dul][x - dul] == 1 ||
					m[y2 - dur][x + dur] == 1 ||
					m[y2 + ddl][x - ddl] == 1 ||
					m[y2 + ddr][x + ddr] == 1)
				{
					foundPos = false;
					break;
				}
				else {
					foundPos = true;
					vu--;
					vd--;
					hl--;
					hr--;
					if (vu < 1 && vd >= 1 && hl >= 1 && hr >= 1) {
						vu = 0;
					}
					if (vd < 1 && vu >= 1 && hl >= 1 && hr >= 1) {
						vd = 0;
					}
					if (hl < 1 && hr >= 1 && vu >= 1 && vd >= 1) {
						hl = 0;
					}
					if (hr < 1 && hl >= 1 && vu >= 1 && vd >= 1) {
						hr = 0;
					}
					dul--;
					dur--;
					ddl--;
					ddr--;
					if (hl > vd) {
						ddl = vd;
					}
					else {
						ddl = hl;
					}

					if (hr > vd) {
						ddr = vd;
					}
					else {
						ddr = hr;
					}
				}
			}
			if (foundPos == true) {
				m[y2][x] = 1;
				foundNext = true;
			}
		}

		for (y = y2 + 1; y < 8; y++) {
			for (x = 0; x < 8; x++) {
				foundPos = false;
				vu = y;
				vd = 7 - y;
				hl = x;
				hr = 7 - x;

				if (hl > vu) {
					dul = vu;
				}
				else {
					dul = hl;
				}

				if (hr > vu) {
					dur = vu;
				}
				else
				{
					dur = hr;
				}

				if (hl > vd) {
					ddl = vd;
				}
				else {
					ddl = hl;
				}

				if (hr > vd) {
					ddr = vd;
				}
				else {
					ddr = hr;
				}

				while (vu > 0 || vd > 0 || hr > 0 || hl > 0) {
					if (m[y - vu][x] == 1 ||
						m[y + vd][x] == 1 ||
						m[y][x - hl] == 1 ||
						m[y][x + hr] == 1 ||
						m[y - dul][x - dul] == 1 ||
						m[y - dur][x + dur] == 1 ||
						m[y + ddl][x - ddl] == 1 ||
						m[y + ddr][x + ddr] == 1)
					{
						foundPos = false;
						break;
					}
					else {
						foundPos = true;
						vu--;
						vd--;
						hl--;
						hr--;
						if (vu < 1 && vd >= 1 && hl >= 1 && hr >= 1) {
							vu = 0;
						}
						if (vd < 1 && vu >= 1 && hl >= 1 && hr >= 1) {
							vd = 0;
						}
						if (hl < 1 && hr >= 1 && vu >= 1 && vd >= 1) {
							hl = 0;
						}
						if (hr < 1 && hl >= 1 && vu >= 1 && vd >= 1) {
							hr = 0;
						}
						dul--;
						dur--;
						ddl--;
						ddr--;
						if (hl > vd) {
							ddl = vd;
						}
						else {
							ddl = hl;
						}

						if (hr > vd) {
							ddr = vd;
						}
						else {
							ddr = hr;
						}
					}
				}
				if (foundPos == true) {
					m[y][x] = 1;
					break;
				}
			}
		}

		//Find & print all queens based on the last constructed board
		for (y = 0; y < 8; y++) {
			cout << "\n";
			for (x = 0; x < 8; x++) {
				if (m[y][x] == 1) {
					qc += 1;
				}
				cout << m[y][x] << " ";
			}
		}
		cout << "Queens placed: " << qc << "\n";
	}


	//Run this outside of for loop when queen counter is 8
	cout << "\n";
	cout << "----Program finished---- \n";
	for (y = 0; y < 8; y++) {
		cout << "\n";
		for (x = 0; x < 8; x++) {
			cout << m[y][x] << " ";
		}
	}
}


int main()
{
	//polynomialCalculus();
	//polynomialMultiplication();
	//polynomialDerivative();
	//palindromeArray();
	QueensPuzzle();
	system("pause");
    return 0;
}

