//References:
//Address: https://cumoodle.coventry.ac.uk/pluginfile.php/1972334/mod_resource/content/0/Binary%20Search%20Tree%20in%20C%2B%2B.cpp
//Author: Diana Hintea

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class StudentNode {
public:
	StudentNode(int id, string name, string dob, string address, int classId, string dateOfEnrolment, bool graduated) {
		this->id = id;
		this->name = name;
		this->dob = dob;
		this->address = address;
		this->classId = classId;
		this->dateOfEnrolment = dateOfEnrolment;
		this->graduated = graduated;
	}

	int id;
	string name;
	string dob;
	string address;
	int classId;
	string dateOfEnrolment;
	bool graduated;

	StudentNode* left;
	StudentNode* right;
	StudentNode* parent;
};

int countChildren(StudentNode* tree, int counter) {

	if (tree->left != NULL) {
		counter += 1;
	}
	if (tree->right != NULL) {
		counter += 1;
	}
	return counter;
}

int findMaxVal(StudentNode* tree, int curMax) {
	if (tree->id > curMax) {
		curMax = tree->id;
	}
	if (tree->right != NULL) {
		findMaxVal(tree->right, curMax);
	}
	return curMax;
}

StudentNode* remove_duplicate_node(StudentNode* tree, int valToCompare) {
	if(tree->id == valToCompare) {
		if (tree->parent != NULL) {
			if (tree->parent->left == tree) {
				if (tree->right != NULL) {
					tree->parent->left = tree->right;
					tree->right->parent = tree->parent;
				}
				else if (tree->left != NULL) {
					tree->parent->left = tree->left;
					tree->left->parent = tree->parent;
				}
				else if (tree->left == NULL && tree->right == NULL) {
					tree->parent->left = NULL;
				}
			}
			else if (tree->parent->right == tree) {
				if (tree->left != NULL) {
					tree->parent->right = tree->left;
					tree->left->parent = tree->parent;
				}
				else if (tree->right != NULL) {
					tree->parent->right = tree->right;
					tree->right->parent = tree->parent;
				}
				else if (tree->left == NULL && tree->right == NULL) {
					tree->parent->left = NULL;
				}
			}
		}
		delete tree;
	}
	else if (tree->id < valToCompare) {
		if (tree->right != NULL) {
			remove_duplicate_node(tree->right, valToCompare);
		}
	}
	else if(tree->id > valToCompare){
		if (tree->left != NULL) {
			remove_duplicate_node(tree->left, valToCompare);
		}
	}
	return tree;
}

StudentNode* check_contents(StudentNode* firstNode, StudentNode* secondNode) {

	//Obtain individual node data for transfer
	StudentNode* firstNodeData = firstNode;
	StudentNode* secondNodeData = secondNode;

	//Locate position of first different character of name string in specified nodes
	int diffChar = 0;

	if (firstNode->name.size() > secondNode->name.size()) {
		for (int i = 0; i < secondNode->name.size(); i++) {
			if (tolower(firstNode->name[i]) != tolower(secondNode->name[i])) {
				diffChar = i;
				break;
			}
		}
	}

	else if (firstNode->name.size() < secondNode->name.size()) {
		for (int i = 0; i < firstNode->name.size(); i++) {
			if (tolower(firstNode->name[i]) != tolower(secondNode->name[i])) {
				diffChar = i;
				break;
			}
		}
	}

	//Obsolete loop
	else if (firstNode->name.size() == secondNode->name.size()) {
		for (int i = 0; i < firstNode->name.size(); i++) {
			if (tolower(firstNode->name[i]) != tolower(secondNode->name[i])) {
				diffChar = i;
				break;
			}
		}
	}

	//Reverse contents of specified nodes based on lexicographic order 
	if (tolower(firstNode->name[diffChar]) > tolower(secondNode->name[diffChar])) {

		firstNode->id = secondNodeData->id;
		firstNode->name = secondNodeData->name;
		firstNode->dob = secondNodeData->dob;
		firstNode->address = secondNodeData->address;
		firstNode->classId = secondNodeData->classId;
		firstNode->dateOfEnrolment = secondNodeData->dateOfEnrolment;
		firstNode->graduated = secondNodeData->graduated;


		secondNode->id = firstNodeData->id;
		secondNode->name = firstNodeData->name;
		secondNode->dob = firstNodeData->dob;
		secondNode->address = firstNodeData->address;
		secondNode->classId = firstNodeData->classId;
		secondNode->dateOfEnrolment = firstNodeData->dateOfEnrolment;
		secondNode->graduated = firstNodeData->graduated;
	}
	return firstNode;
}

StudentNode* student_insert_by_id(StudentNode* tree, int id, string name, string dob, string address, int classId, string dateOfEnrolment, bool graduated) {
	if (tree == NULL) {
		tree = new StudentNode(id, name, dob, address, classId, dateOfEnrolment, graduated);
		tree->parent = NULL;
	}
	else {
		if (id < tree->id)
			if (tree->left == NULL) {
				tree->left = new StudentNode(id, name, dob, address, classId, dateOfEnrolment, graduated);
				tree->left->parent = tree;
			}
			else
				student_insert_by_id(tree->left, id, name, dob, address, classId, dateOfEnrolment, graduated);
		else
			if (tree->right == NULL) {
				tree->right = new StudentNode(id, name, dob, address, classId, dateOfEnrolment, graduated);
				tree->right->parent = tree;
			}
			else
				student_insert_by_id(tree->right, id, name, dob, address, classId, dateOfEnrolment, graduated);
	}
	return tree;
}

StudentNode* student_insert_by_name(StudentNode* tree, int id, string name, string dob, string address, int classId, string dateOfEnrolment, bool graduated) {
	if (tree == NULL) {
		tree = new StudentNode(id, name, dob, address, classId, dateOfEnrolment, graduated);
		tree->parent = NULL;
	}
	else {
		int diffChar = 0;
		if (name.size() > tree->name.size()) {
			for (int i = 0; i < tree->name.size(); i++) {
				if (tolower(name[i]) != tolower(tree->name[i])) {
					diffChar = i;
					break;
				}
			}
		}

		else if (name.size() < tree->name.size()) {
			for (int i = 0; i < name.size(); i++) {
				if (tolower(name[i]) != tolower(tree->name[i])) {
					diffChar = i;
					break;
				}
			}
		}
		else if (name.size() == tree->name.size()) {
			for (int i = 0; i < name.size(); i++) {
				if (tolower(name[i]) != tolower(tree->name[i])) {
					diffChar = i;
					break;
				}
			}
		}

		if (tolower(name[diffChar]) < tolower(tree->name[diffChar])) {
			if (tree->left == NULL) {
				tree->left = new StudentNode(id, name, dob, address, classId, dateOfEnrolment, graduated);
				tree->left->parent = tree;
			}

			else {
				student_insert_by_name(tree->left, id, name, dob, address, classId, dateOfEnrolment, graduated);
			}
		}
		else if (tolower(name[diffChar]) > tolower(tree->name[diffChar])) {
			if (tree->right == NULL) {
				tree->right = new StudentNode(id, name, dob, address, classId, dateOfEnrolment, graduated);
				tree->right->parent = tree;
			}
			else {
				student_insert_by_name(tree->right, id, name, dob, address, classId, dateOfEnrolment, graduated);
			}
		}
	}
	return tree;
}

StudentNode* find_by_id(StudentNode* tree, int searchId = NULL) {
	if (searchId == NULL) {
		cout << "Insert student ID to search: ";
		//Input validation for ID value specification
		while (!(cin >> searchId) || searchId <= 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}
	}

	if (tree != NULL) {
		if (tree->id > searchId) {
			find_by_id(tree->left);
		}
		else if (tree->id < searchId) {
			find_by_id(tree->right);
		}
		else if (tree->id == searchId) {
			cout << "Student Details: \n";
			cout << "ID: " << tree->id << "\n";
			cout << "Name: " << tree->name << "\n";
			cout << "Date of Birth: "<< tree->dob << "\n";
			cout << "Address: " << tree->address << "\n";
			cout << "Class ID: " <<tree->classId << "\n";
			cout << "Date  of Enrolment: " << tree->dateOfEnrolment << "\n";
			if (tree->graduated == false) {
				cout << "Status: Undergraduate" << "\n";
			}
			else if(tree->graduated == true) {
				cout << "Status: Graduate" << "\n";
			}
			bool updateDetails;
			string inputConvert;
			cout << "Would you like to make changes? \n";
			while (!(cin >> inputConvert) || inputConvert != "Yes" || inputConvert != "yes" ||
				inputConvert != "No" || inputConvert != "no")
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Try again: ";
			}

			//Convert into non-case sensitive input and continue based on the user's choice
			for (int i = 0; i < inputConvert.size(); i++) {
				inputConvert[i] = putchar(tolower(inputConvert[i]));
			}
			if (inputConvert == "yes") {
				updateDetails = true;
				cout << "\n";
			}
			else if (inputConvert == "no") {
				updateDetails = false;
				cout << "\n";
				return tree;
			}

			if (updateDetails == true) {

				string updatedName;
				string updatedDOB;
				string updatedAddress;
				int updatedClassID;
				string updatedDOE;
				string updatedStatus;
				
				//Check previous data and update it if newest input is different
				cout << "Enter Name: ";
				while (!(cin >> updatedName)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Try again: ";
				}
				if (updatedName != tree->name) {
					updatedName[0] = putchar(toupper(updatedName[0]));
					tree->name = updatedName;
				}

				cout << "Enter Date of Birth: (dd/mm/yy): ";
				while (!(cin >> updatedDOB)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Try again: ";
				}
				if (updatedDOB != tree->dob) {
					tree->dob = updatedDOB;
				}

				cout << "Enter Address: ";
				while (!(cin >> updatedAddress)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Try again: ";
				}
				if (updatedAddress != tree->address) {
					tree->address = updatedAddress;
				}

				cout << "Enter Class ID: ";
				while (!(cin >> updatedClassID)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Try again: ";
				}
				if (updatedClassID != tree->classId) {
					tree->classId = updatedClassID;
				}

				cout << "Enter Date of Enrolment: (dd/mm/yy) ";
				while (!(cin >> updatedDOE)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Try again: ";
				}
				if (updatedDOE != tree->dateOfEnrolment) {
					tree->dateOfEnrolment = updatedDOE;
				}

				cout << "Enter Status (Graduate/Undergraduate): ";
				while (!(cin >> updatedStatus) || updatedStatus != "Graduate" || updatedStatus != "graduate" || 
					updatedStatus != "Undergraduate" || updatedStatus != "undergraduate") {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Try again: ";
				}
				//Convert into non-case sensitive input
				for (int i = 0; i < updatedStatus.size(); i++) {
					updatedStatus[i] = putchar(tolower(updatedStatus[i]));
				}
				if (updatedStatus == "graduate") {
					tree->graduated = true;
				}
				else if (updatedStatus == "undergraduate") {
					tree->graduated = false;
				}
			}
			cout << "\n";
			cout << "Student Details: \n";
			cout << "ID: " << tree->id << "\n";
			cout << "Name: " << tree->name << "\n";
			cout << "Date of Birth: " << tree->dob << "\n";
			cout << "Address: " << tree->address << "\n";
			cout << "Class ID: " << tree->classId << "\n";
			cout << "Date  of Enrolment: " << tree->dateOfEnrolment << "\n";
			if (tree->graduated == false) {
				cout << "Status: Undergraduate" << "\n";
			}
			else if (tree->graduated == true) {
				cout << "Status: Graduate" << "\n";
			}
		}
	}
	return tree;
}

StudentNode* find_next_viable(StudentNode* tree, int valueToSearch) {
	if (tree != NULL) {
		if (tree->id == valueToSearch) {
			return tree;
		}
		else if (tree->left != NULL) {
			find_next_viable(tree->left, valueToSearch);
		}
	}
	return tree;
}

StudentNode* statusSort(StudentNode* tree, bool graduateStatus) {
	if (tree != NULL) {
		if (tree->graduated == graduateStatus) {
			cout << "Student Details: \n";
			std::cout << tree->id << std::endl;
			std::cout << tree->name << std::endl;
			std::cout << tree->dob << std::endl;
			std::cout << tree->address << std::endl;
			std::cout << tree->classId << std::endl;
			std::cout << tree->dateOfEnrolment << std::endl;
			if (tree->graduated == true) {
				cout << "Graduate \n";
			}
			else if (tree->graduated == false) {
				cout << "Undergraduate \n";
			}
			cout << "------------------------- \n";
		}
		if (tree->left != NULL) {
			statusSort(tree->left, graduateStatus);
		}
		if (tree->right != NULL) {
			statusSort(tree->right, graduateStatus);
		}
	}
	return tree;
}

StudentNode* displayByStatusFromClass(StudentNode* tree, bool graduateStatus, int searchedClassId = NULL) {
	if (searchedClassId == NULL) {
		cout << "Insert class ID to search: ";
		while (!(cin >> searchedClassId) || searchedClassId <= 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}
	}

	if (tree != NULL) {
		if (tree->left != NULL) {
			displayByStatusFromClass(tree->left, graduateStatus, searchedClassId);
		}
		if (tree->graduated == graduateStatus && tree->classId == searchedClassId) {
			std::cout << tree->id << std::endl;
			std::cout << tree->name << std::endl;
			std::cout << tree->dob << std::endl;
			std::cout << tree->address << std::endl;
			std::cout << tree->classId << std::endl;
			std::cout << tree->dateOfEnrolment << std::endl;
			if (tree->graduated == true) {
				cout << "Graduate \n";
			}
			else {
				cout << "Undergraduate \n";
			}
			cout << "------------------------- \n";
		}
		if (tree->right != NULL) {
			displayByStatusFromClass(tree->right, graduateStatus, searchedClassId);
		}
	}
	return tree;
}

StudentNode* displayFromClass(StudentNode* tree, int searchedClassId = NULL) {
	if (searchedClassId == NULL) {
		cout << "Insert class ID to search: ";
		while (!(cin >> searchedClassId) || searchedClassId <= 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}
	}
	if (tree != NULL) {
		if (tree->left != NULL) {
			displayFromClass(tree->left,searchedClassId);
		}
		if (tree->classId == searchedClassId) {
			std::cout << tree->id << std::endl;
			std::cout << tree->name << std::endl;
			std::cout << tree->dob << std::endl;
			std::cout << tree->address << std::endl;
			std::cout << tree->classId << std::endl;
			std::cout << tree->dateOfEnrolment << std::endl;
			if (tree->graduated == true) {
				cout << "Graduate \n";
			}
			else {
				cout << "Undergraduate \n";
			}
			cout << "------------------------- \n";
		}
		if (tree->right != NULL) {
			displayFromClass(tree->right, searchedClassId);
		}
	}
	return tree;
}

StudentNode* delete_by_id(StudentNode* tree, int searchId = NULL) {
	if (searchId == NULL) {
		cout << "Insert ID of student to delete: ";
		while (!(cin >> searchId) || searchId <= 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again: ";
		}
	}
	int childCounter = 0;
	int maxSubTreeVal = 0;
	if (tree != NULL) {
		if (tree->id > searchId) {
			delete_by_id(tree->left);
		}
		else if (tree->id < searchId) {
			delete_by_id(tree->right);
		}
		else if (tree->id == searchId) {
			childCounter = 0;
			maxSubTreeVal = 0;
			childCounter = countChildren(tree, childCounter);
			if (childCounter == 0) {
				if (tree->parent->left == tree) {
					tree->parent->left = NULL;
				}
				if (tree->parent->right == tree) {
					tree->parent->right = NULL;
				}
				delete tree;
			}
			if (childCounter == 1) {
				if (tree->parent != NULL) {
					if (tree->parent->left == tree) {
						if (tree->right != NULL) {
							tree->parent->left = tree->right;
							tree->right->parent = tree->parent;
						}
						else if (tree->left != NULL) {
							tree->parent->left = tree->left;
							tree->left->parent = tree->parent;
						}
					}
					else if (tree->parent->right == tree) {
						if (tree->left != NULL) {
							tree->parent->right = tree->left;
							tree->left->parent = tree->parent;
						}
						else if (tree->right != NULL) {
							tree->parent->right = tree->right;
							tree->right->parent = tree->parent;
						}
					}
				}
				delete tree;
			}
			else if (childCounter > 1) {
				maxSubTreeVal = 0;
				maxSubTreeVal = findMaxVal(tree->left, maxSubTreeVal);
				StudentNode* replacement = find_next_viable(tree->left, maxSubTreeVal);

				tree->id = replacement->id;
				tree->name = replacement->name;
				tree->dob = replacement->dob;
				tree->address = replacement->address;
				tree->classId = replacement->classId;
				tree->dateOfEnrolment = replacement->dateOfEnrolment;
				tree->graduated = replacement->graduated;

				remove_duplicate_node(tree->left, tree->id);
			}
		}
	}
	return tree;
}

StudentNode* delete_by_status(StudentNode* tree, bool graduated) {
	int childCounter = 0;
	int maxSubTreeVal = 0;
	StudentNode* parentLoc = NULL;
	if (tree != NULL) {
		if (tree->graduated != graduated) {
			if (tree->left != NULL) {
				delete_by_status(tree->left,graduated);
			}

			if (tree->right != NULL) {
				delete_by_status(tree->right,graduated);
			}
		}
		else if(tree->graduated == graduated){
			childCounter = countChildren(tree, childCounter);
			if (childCounter == 0) {
				if (tree->parent != NULL) {
					if (tree->parent->left == tree) {
						tree->parent->left = NULL;
					}
					else if (tree->parent->right == tree) {
						tree->parent->right = NULL;
					}
				}
				delete tree;
			}
			else if (childCounter == 1) {
				parentLoc = NULL;
				if (tree->parent != NULL) {
					parentLoc = tree->parent;
				}
				if (tree->parent->left == tree) {
					if (tree->right != NULL) {
						tree->parent->left = tree->right;
						tree->right->parent = tree->parent;
					}
					else if (tree->left != NULL) {
						tree->parent->left = tree->left;
						tree->left->parent = tree->parent;
					}
				}
				else if (tree->parent->right == tree) {
					if (tree->left != NULL) {
						tree->parent->right = tree->left;
						tree->left->parent = tree->parent;
					}
					else if (tree->right != NULL) {
						tree->parent->right = tree->right;
						tree->right->parent = tree->parent;
					}
				}
				delete tree;
				if (parentLoc != NULL) {
					delete_by_status(parentLoc, graduated);
				}
			}
			else if (childCounter > 1) {
				maxSubTreeVal = 0;
				parentLoc = NULL;
				if (tree->parent != NULL) {
					parentLoc = tree->parent;
				}
				maxSubTreeVal = findMaxVal(tree->left, maxSubTreeVal);
				StudentNode* replacement = find_next_viable(tree->left, maxSubTreeVal);

				tree->id = replacement->id;
				tree->name = replacement->name;
				tree->dob = replacement->dob;
				tree->address = replacement->address;
				tree->classId = replacement->classId;
				tree->dateOfEnrolment = replacement->dateOfEnrolment;
				tree->graduated = replacement->graduated;

				remove_duplicate_node(tree->left, tree->id);
				if (parentLoc != NULL) {
					delete_by_status(parentLoc, graduated);
				}
			}
		}
	}
	return tree;
}

void postorder(StudentNode* tree) {
	if (tree->left != NULL)
		postorder(tree->left);
	if (tree->right != NULL)
		postorder(tree->right);
		std::cout << tree->id << std::endl;
		std::cout << tree->name << std::endl;
		std::cout << tree->dob << std::endl;
		std::cout << tree->address << std::endl;
		std::cout << tree->classId << std::endl;
		std::cout << tree->dateOfEnrolment << std::endl;
	if (tree->graduated == true) {
		cout << "Graduate \n";
	}
	else {
		cout << "Undergraduate \n";
	}
	cout << "------------------------- \n";
}

void in_order(StudentNode* tree) {
	if (tree->left != NULL)
		in_order(tree->left);
	std::cout << tree->id << std::endl;
	std::cout << tree->name << std::endl;
	std::cout << tree->dob << std::endl;
	std::cout << tree->address << std::endl;
	std::cout << tree->classId << std::endl;
	std::cout << tree->dateOfEnrolment << std::endl;
	if (tree->graduated == true) {
		cout << "Graduate \n";
	}
	else {
		cout << "Undergraduate \n";
	}
	cout << "------------------------- \n";
	if (tree->right != NULL)
		in_order(tree->right);
}

int main(int argc, char *argv[])
{
	//Binary search tree sorted based on student ID data
	StudentNode* t = student_insert_by_id(0, 4, "Jimmy", "15/03/96","Baskerville", 101, "15/09/15",false);
	student_insert_by_id(t, 6, "Donny", "11/11/96", "Baskerville", 101, "15/09/15", true);
	student_insert_by_id(t, 3, "Robert", "10/01/96", "Baskerville", 102, "15/09/15", false);
	student_insert_by_id(t, 5, "Roxana", "10/10/96", "Baskerville", 102, "15/09/15", false);
	student_insert_by_id(t, 7, "Angela", "10/03/96", "Baskerville", 102, "15/09/15", false);
	student_insert_by_id(t, 2, "Billy", "11/11/96", "Baskerville", 101, "15/09/15", true);
	student_insert_by_id(t, 1, "Ben", "11/11/96", "Baskerville", 101, "15/09/15", true);


	//Tree sorted lexicographically based on name data
	StudentNode* n = student_insert_by_name(0, 4, "Jimmy", "15/03/96", "Baskerville", 101, "15/09/15", false);
	student_insert_by_name(n, 6, "Donny", "11/11/96", "Baskerville", 101, "15/09/15", true);
	student_insert_by_name(n, 5, "Roxana", "10/10/96", "Baskerville", 102, "15/09/15", false);
	student_insert_by_name(n, 3, "Robert", "10/01/96", "Baskerville", 102, "15/09/15", false);
	student_insert_by_name(n, 7, "Angela", "10/03/96", "Baskerville", 102, "15/09/15", false);
	student_insert_by_name(n, 2, "Billy", "11/11/96", "Baskerville", 101, "15/09/15", true);
	student_insert_by_name(n, 1, "Ben", "11/11/96", "Baskerville", 101, "15/09/15", true);

	//Find a student by his/hers unique code, and support updating of the student info if found.
	//find_by_id(t);

	//List students by class in lexicographic order of their names. 
	//displayFromClass(n);
	
	//List all graduated students. 
	//statusSort(t, true);

	//List all undergrads by their class in lexicographic order of their names. 
	//displayByStatusFromClass(n, false);

	//Delete a student given by its code. 
	//delete_by_id(t);
	//in_order(t);

	//Delete all graduatesc
	//delete_by_status(t, true);
	//in_order(t);

	//List all students in lexicographic order of their names. 
	//in_order(n);
	system("pause");
	return 0;
}
