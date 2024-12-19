//References:
//Address: https://www.uow.edu.au/~lukes/TEXTBOOK/notes-cpp/io/readtextfile.html
//Author: University of Wollongong / Fred Swartz
//Address: https://cumoodle.coventry.ac.uk/pluginfile.php/1969082/mod_resource/content/0/C%2B%2B%20Double%20Linked%20List%20Source%20Code.txt
//Author: Diana Hintea

#include "stdafx.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Node
{
public:
	string value; //This could really be any type
	Node* next;
	Node* prev;
	Node(string val) {
		std::cout << "Node constructr!" << std::endl;
		this->value = val;
		this->next = (Node*)0;
		this->prev = (Node*)0;
	}
	~Node() {
		std::cout << "Node destructor" << std::endl;
		std::cout << "I had the value " << this->value << std::endl;
	}
};
class List
{

public:
	Node* head;
	Node* tail;

	List() {
		std::cout << "List Constructor!" << std::endl;
		this->head = 0;
		this->tail = 0;
	}
	~List() {
		std::cout << "List destructor!" << std::endl;
		std::cout << "Todo: properly delete nodes..." << std::endl;
	}
	void insert(Node* n, Node* x) {
		//Not actually perfect: how do we prepend to an existing list?
		if (n != 0) {
			x->next = n->next;
			n->next = x;
			x->prev = n;
			if (x->next != 0)
				x->next->prev = x;
		}
		if (this->head == 0) {
			this->head = x;
			this->tail = x;
			x->prev = 0;
			x->next = 0;
		}
		else if (this->tail == n) {
			this->tail = x;
		}
	}
	void display() {
		Node* i = this->head;
		std::cout << "List: ";
		while (i != 0) {
			if (i != this->tail) {
				std::cout << i->value << " ";
			}
			else {
				std::cout << i->value;
			}
			i = i->next;
		}
		std::cout << std::endl;
		//std::cout << "Tail: " << this->tail->value << std::endl;
	}
	void delete_first() {
		Node* p;
		if (this->head != NULL) {
			p = this->head;
			this->head = this->head->next;
			delete p;
		}
		if (this->head == NULL) {
			this->tail = NULL;
		}
	}
	void delete_last() {
		Node* p, *p1;
		p1 = NULL;
		p = this->head;
		if (p != NULL) {

			while (p != this->tail) {
				p1 = p;
				p = p->next;
			}

			if (p == this->head) {
				this->head = this->tail = NULL;
			}
			else {
				p1->next = NULL;
				this->tail = p1;
			}
			delete p;
		}
	}
	void delete_selected(string key) {
		Node *p, *p1;
		p1 = NULL;
		p = this->head;
		while (p != NULL) {
			if (p->value == key) {
				break;
			}
			p1 = p;
			p = p->next;
		}
		if (p != NULL) {
			if (p == this->head) {
				this->head = this->head->next;
				delete p;
				if (this->head == NULL) {
					this->tail = NULL;
				}
			}
			else {
				p1->next = p->next;
				if (p == this->tail) {
					this->tail = p1;
				}
				delete p;
			}
		}
	}
	void delete_duplicates() {
		Node *c, *p;
		bool deleted = false;
		c = this->head;
		p = this->head->next;
		if (this->head != NULL && this->head->next != NULL) {
			while (c != this->tail)
			{
				if (deleted) {
					p = c->next;
				}
				if (c->value != p->value) {
					deleted = false;
					if (p != this->tail) {
						p = p->next;
					}
					else {
						c = c->next;
						p = c->next;
					}
				}
				else {
					deleted = true;
					if (p != this->tail) {
						p->prev->next = p->next;
						p->next->prev = p->prev;
					}
					else if (p == this->tail) {
						this->tail = p->prev;
						p->prev->next = NULL;
						p->prev = this->tail;
					}
					delete p;
				}
			}
		}
	}
	void sort_alphabetically() {
		Node *p, *n;
		string vp, vn;
		p = this->head;
		n = this->head->next;
		while (n != NULL)
		{
			p->value.at(0) = putchar(tolower(p->value.at(0)));
			n->value.at(0) = putchar(tolower(n->value.at(0)));
			if (p->value.at(0) > n->value.at(0)) {
				vp = n->value;
				vn = p->value;
				p->value = vp;
				n->value = vn;
			}
			n = n->next;
			if (n == this->tail) {
				p = p->next;
				n = p->next;
			}
		}
	}
};

void ReadInputFile() {
	//Creating a list to store the data
	ifstream inFile;
	string word;
	string prevWord;
	int prevLen;

	//Container each unique word length gathered from reading the file
	vector<int> wordLength;
	//Container for pointers to the head nodes of each new list made to hold unique word lengths
	vector<List*> listAdress;

	List *l = new List();

	inFile.open("C:\\Users\\kriss\\Desktop\\Lore.txt");

	//Program validation for reading the text file
	if (!inFile) {
		cout << "Unable to open file specified file ";
	}

	//Get the first word and store its data for initialisation
	if (inFile >> word) {
		prevWord = word;
		prevLen = word.length();
		wordLength.push_back(word.length());
		l->insert(0, new Node(word));
		listAdress.push_back(l);
	}

	//Get all of the different word lengths from the text file being read and plug them into lists representing a unique length
	for (int i = 0; i < wordLength.size(); i++) {
		while (inFile >> word)
		{
			//Iterate through the text file inserting words of the same length to their corrensponding lists 
			//until a word with a different length compared to the last one is read
			if (word.length() == prevLen) {
				l->insert(l->head, new Node(word));
			}
			else {
				//Check if the length of the currently read string already exist in the word length collection
				bool distinctLength;
				for (int j = 0; j < wordLength.size(); j++) {
					if (word.length() != wordLength[j]) {
						distinctLength = true;
					}
					else {
						distinctLength = false;
						break;
					}
				}
				//Add the unique word length found to the word length collection,
				//create a new list to store words from the text file of this length and
				//add the head node of the new list to the vector pointing to the address (head node) of each list
				if (distinctLength) {
					wordLength.push_back(word.length());
					List *nl = new List();
					nl->insert(0, new Node(word));
					listAdress.push_back(nl);
				}
				//Check which lists stores strings of the same length and add the current word being read in there
				else {
					for (int i = 0; i < listAdress.size(); i++) {
						if (word.length() == listAdress[i]->head->value.length()) {
							listAdress[i]->insert(listAdress[i]->head, new Node(word));
						}
					}
				}
			}
		}
	}
	inFile.close();


	//Remove duplicate nodes in each list and sort nodes alphabetically
	for (int i = 0; i < listAdress.size(); i++) {
		listAdress[i]->delete_duplicates();
		listAdress[i]->sort_alphabetically();
	}
	cout << "\n";

	//Print sorted lists and provide information on each node's length and string data
	for (int i = 0; i < listAdress.size(); i++) {
		cout << "List(" << i << "): Word length: " << wordLength[i] << ", data: ";
		listAdress[i]->display();
	}
}

int main(int argc, char *argv[])
{
	ReadInputFile();
	system("pause");
	return 0;
}

