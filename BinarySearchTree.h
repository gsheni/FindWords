/*
 * BinarySearchTree.h
 *
 *  Created on: Feb 14, 2014
 *      Author: gaurav
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

template <typename Comparable>
class BinarySearchTree
{
	public:
	BinarySearchTree()
	:root{nullptr}
	{}

	//for copying
	BinarySearchTree(const BinarySearchTree & rhs):root{nullptr}{
		root = clone(rhs.root);
	}

	//this is for moving
	BinarySearchTree(BinarySearchTree && rhs):root{rhs.root}{
		rhs.root = nullptr;
	}

	//the destructor!
	~BinarySearchTree(){
		makeEmpty();
	}

	//get smallest item
	const Comparable & findMin() const{
		return findMin(root)->element;
	}

	//get largest item
	const Comparable & findMax() const{
		return findMax(root)->element;
	}

	//to see if the tree has something.
	bool contains(const Comparable & x) const{
		return contains(x, root);
	}

	// to see if the tree is empty.
	bool isEmpty() const{
	return root == nullptr;
	}

	// to print the tree in order
	void printTree(ostream & out = cout) const{
		if(isEmpty())
			out << "Empty tree" << endl;
		else{
			printTree(root, out);
		}
	}

	// make the tree empty.
	void makeEmpty(){
		makeEmpty(root);
	}

	// to insert something into the tree
	void insert(const Comparable & x){
		insert(x, root);
	}

	// to insert something into the tree
	void insert(Comparable && x){
		insert(std::move(x), root);
	}

	//to take out x from the tree
	void remove(const Comparable & x){
		remove(x, root);
	}

	//this overloads the operator "=" and copies the input
	BinarySearchTree & operator=(const BinarySearchTree & rhs){
		BinarySearchTree copyinput;//create temporary binarysearchtree
		copyinput = rhs;
		std::swap(*this,copyinput); //Exchange values of two objects
		return *this;
	}

	//this overloads the operator "=" and copies the input
	BinarySearchTree & operator=(BinarySearchTree && rhs){
		std::swap(root,rhs.root); //Exchange values of two objects
		return *this;
	}

	//function to get full height of tree
	int height() {
		return height(root);
	}

	//function to get left subtree height
	int leftheight(){
		int leftsubtree = leftheight(root);
		return leftsubtree;
	}

	//function to get right subtree height
	int rightheight(){
		int rightsubtree = rightheight(root);
		return rightsubtree;
	}

	//to print out the tree
	void printHeight(ostream & out = cout){
		int heightnum = height();
		int leftheightnum = leftheight();
		int rightheightnum = rightheight();
		cout << "Tree Height: " << heightnum << " (Left Subtree: " << leftheightnum << ") (Right Subtree: " << rightheightnum << ")" << "\n";
	}

  private:
	struct BinaryNode{
	Comparable element; //the type will depend on type given, such as string, will mean element.
	BinaryNode *left; //left of element, subtree
	BinaryNode *right; //right of element, subtree

	BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
	  : element{theElement}, left{lt}, right{rt} {}

	BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
	  : element{std::move(theElement)}, left{lt}, right{rt} {}
	};

	BinaryNode *root; //the starting point, the stem of the tree

	//to insert things into the tree. the x is the input, the t is the root.
	//makes a new binarynode, which is the new root if there isn't one
	//keeps moving left or right, depending on what the oder of input, since its recursive function.
	void insert(const Comparable & x, BinaryNode * & t){
		if(t == nullptr){
		    t = new BinaryNode{x, nullptr, nullptr};
		}
		else if(x < t->element)
		    insert(x, t->left);
		else if(t->element < x)
		    insert(x, t->right);
		else{
		    ;  //duplicate
		}
	}

	//to insert things into the tree. the x is the input, the t is the root.
	//makes a new binarynode, which is the new root if there isn't one
	//keeps moving left or right, depending on what the oder of input, since its recursive function.
	void insert(Comparable && x, BinaryNode * & t){
		if(t == nullptr){
		    t = new BinaryNode{std::move(x), nullptr, nullptr};
		}
		else if(x < t->element){
		    insert(std::move(x), t->left);
		}
		else if(t->element < x){
		    insert(std::move(x), t->right);
		}
		else{
		    ;  //duplicate
		}
	}

	//to take out things from the subtree. the x is the input to remove, the t is the root.
	//makes the new root
	void remove(const Comparable & x, BinaryNode * & t){
		if(t == nullptr){
		    return;   //item not found
		}
		if(x < t->element){
		    remove(x, t->left);
		}
		else if(t->element < x){
		    remove(x, t->right);
		}
		else if(t->left != nullptr && t->right != nullptr) //2 children
		{
		    t->element = findMin(t->right)->element;
		    remove(t->element, t->right);
		}
		else
		{
		    BinaryNode *oldNode = t;
		    t = (t->left != nullptr) ? t->left : t->right;
		    delete oldNode;
		}
	}

	//find smallest item in tree
	BinaryNode * findMin(BinaryNode *t) const{
		if(t == nullptr)
		    return nullptr;
		if(t->left == nullptr)
		    return t;
		return findMin(t->left);
	}

	//find biggest item in tree
	BinaryNode * findMax(BinaryNode *t) const{
		if(t != nullptr)
		    while(t->right != nullptr)
			t = t->right;
		return t;
	}

	//to find the item in the tree, the x is the input and the t is the root.
	bool contains(const Comparable & x, BinaryNode *t) const{
		if(t == nullptr)
		    return false;
		else if(x < t->element)
		    return contains(x, t->left);
		else if(t->element < x)
		    return contains(x, t->right);
		else
		    return true;    // Match
	}

	//make tree empty.
	void makeEmpty(BinaryNode * & t){
		if(t != nullptr)
		{
		    makeEmpty(t->left);
		    makeEmpty(t->right);
		    delete t;
		}
		t = nullptr;
	}

	//to print the tree
	void printTree(BinaryNode *t, ostream & out) const{
		if(t != nullptr)
		{
		printTree(t->left, out);
		out << t->element << "\n";
		printTree(t->right, out);
		}
	}

	//to make a copy of the tree
	BinaryNode * clone(BinaryNode *t) const{
		if(t == nullptr)
		    return nullptr;
		else
		    return new BinaryNode{t->element, clone(t->left), clone(t->right)};
	}

	//to find height of full tree.
	int height (BinaryNode *t){
		if(t == nullptr){
			return -1;
		}
		else{
			return 1 + max(height(t->left),height(t->right));
		}
	}

	// to find the left height subtree
	int leftheight(BinaryNode *t){
		if(t == nullptr){
			return -1;
		}
		else{
			return height(t->left);
		}
	}

	// to find the right height subtree
	int rightheight(BinaryNode *t){
		if(t == nullptr){
			return -1;
		}
		else{
			return height(t->right);
		}
	}
};

#endif /* BINARYSEARCHTREE_H_ */

