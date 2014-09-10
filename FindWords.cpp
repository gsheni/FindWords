/*
Gaurav Sheni
CSC 221
Project 2 - FindWords
2/19/14
 */
#include <iostream>
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream> // Needed to read text file.

using namespace std;

int main (int argc, char **argv){
	BinarySearchTree<string> searchtree; //create the binary searchtree, of string type
	AvlTree<string> avltree; //create the avl search tree, of string type
	if (argc != 3){ //if there is an incorrect number of arguments, which means the arguments have to equal 3
		cout << "Incorrect Number of Command Line Arguments" << endl;
		exit(1);//exit program
	}
	string filetoopen = string(argv[1]); // the second input has to be the file name so convert it to a string
	if (string(argv[2]) == "BST"){
		string currentword; //string to hold the current word being read.
		ifstream wordfile(filetoopen); // This uses the ifstream class to open and read the text file line by line
			if (wordfile.is_open()){ //as long as the ifstream is open
				while(getline(wordfile, currentword)) { //as long as there is lines in the file, grab it line by line
					searchtree.insert(currentword); //insert it into the tree, the current line
				}
				wordfile.close(); //close the fstream, save memory.
			}
			else {
				cout << "Can't open the file. Wrong filename or doesn't exist." << endl;
				exit(1);
			}
		searchtree.printHeight();
		string input; //for string to search database
		cout << "Please enter a word to search:" << endl;
		cin >> input;
		while (input != "sortie"){ //if the user wants to exit
			if (searchtree.contains(input)){ //to make sure the database has the word
			cout << "Yes" << endl;
			}
			else {
			cout << "No" << endl;
			}
		cout << "Please enter a word to search:" << endl;
		cin >> input;
		}
	searchtree.makeEmpty(); //empty tree, save memory.
	exit(1);
	}
	else if (string(argv[2]) == "AVL"){
		cout << "Please wait ~1 minute." << endl;
		string currentword;//string to hold the current word being read.
		ifstream wordfile(filetoopen); // This uses the ifstream class to open and read the text file line by line
			if (wordfile.is_open()){//as long as the ifstream is open
				while(getline(wordfile, currentword)) {//as long as there is lines in the file, grab it line by line
					avltree.insert(currentword);//insert it into the tree, the current line
				}
				wordfile.close();  //close the fstream, save memory.
			}
			else {
				cout << "Can't open the file. Wrong filename or doesn't exist." << endl;
				exit(1);
			}
		avltree.printHeight();
		cout << "Please enter a word to search:" << endl;
		string input;
		cin >> input;
		while (input != "sortie"){ //if the user wants to exit
			if (avltree.contains(input)){ //to make sure the database has the word
			cout << "Yes" << endl;
			}
			else {
			cout << "No" << endl;
			}
		cout << "Please enter a word to search:" << endl;
		cin >> input;
		}
	avltree.makeEmpty(); //empty tree, save memory.
	exit(1);
	}
}
