/*
 * AVLTree.h
 *
 *  Created on: Feb 14, 2014
 *      Author: gaurav
 */

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream>
using namespace std;

template <typename Comparable>
class AvlTree
{
public:
	AvlTree()
	:root{nullptr}
	{}

	//the copy constructor
	AvlTree(const AvlTree & rhs):root{nullptr}{
	root = clone(rhs.root);
	}

	//this is for moving
	AvlTree(AvlTree && rhs):root{rhs.root}{
	rhs.root = nullptr;
	}

	//the destructor!
	~AvlTree(){
	makeEmpty();
	}

	//to get the smallest in the tree
	const Comparable & findMin() const{
		if(isEmpty())
		return findMin(root)->element;
	}

	//to get the largest in the tree
	const Comparable & findMax() const{
		if(isEmpty())
		return findMax(root)->element;
	}

	//to see if the tree has something
	bool contains(const Comparable & x) const{
		return contains(x, root);
	}

	// to see if the tree is empty.
	bool isEmpty() const{
		return root == nullptr;
	}

	//to print out the tree
	void printTree(ostream & out = cout) const{
		if (isEmpty()){
		out << "Empty Tree" <<endl;
		}
		else {
		printTree(root,out);
		}
	}

	//to make the tree empty
	void makeEmpty(){
		makeEmpty(root);
	}

	//to put something into the tree
	void insert(const Comparable & x){
		insert(x, root);
	}

	//to put something into the tree
	void insert(Comparable && x){
		insert(std::move(x), root);
	}

	//to take something out of the tree
	void remove(const Comparable & x){
		remove(x, root);
	}

	//this overloads the operator and copys the input
	AvlTree & operator=(const AvlTree & rhs){
		AvlTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	//this overloads the operator and copys the input
	AvlTree & operator=(AvlTree && rhs){
		std::swap(root, rhs.root);
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

	void printHeight(ostream & out = cout){
		int heightnum = height();
		int leftheightnum = leftheight();
		int rightheightnum = rightheight();
		cout << "Tree Height: " << heightnum << " (Left Subtree: " << leftheightnum << ") (Right Subtree: " << rightheightnum << ")" << "\n";
	}

private:
	struct AvlNode{
	Comparable element;
	AvlNode   *left;
	AvlNode   *right;
	int       height;

	AvlNode(const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0)
	  : element{ele}, left{lt}, right{rt}, height{h} {}

	AvlNode(Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0)
	  : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
	};

	AvlNode *root;

	//find full height of tree, if no height, say -1
	int height (AvlNode *t){
		if(t == nullptr){
			return -1;
		}
		else{
			return 1 + max(height(t->left),height(t->right));
		}
	}

  	//to insert things into the tree. the x is the input, the t is the root.
	//makes a new binarynode, which is the new root if there isn't one
	//keeps moving left or right, depending on what the oder of input, since its recursive function.
	void insert(const Comparable & x, AvlNode * & t){
		if(t == nullptr)
		    t = new AvlNode{x, nullptr, nullptr};
		else if(x < t->element)
		    insert(x, t->left);
		else if(t->element < x)
		    insert(x, t->right);

		balance(t);
	}

	static const int ALLOWED_IMBALANCE = 1; // the avl tree is allowed to be 1 off from each other, but no more than 1

	//this balances the avl tree, so the left and right are equal or within 1.
	void balance(AvlNode * & t){
		if(t == nullptr)
		    return;

		if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
		    if(height(t->left->left) >= height(t->left->right))
			rotateWithLeftChild(t);
		    else
			doubleWithLeftChild(t);
		else
		if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
		    if(height(t->right->right) >= height(t->right->left))
			rotateWithRightChild(t);
		    else
			doubleWithRightChild(t);

		t->height = max(height(t->left), height(t->right)) + 1;
	}

	//this rotates the binary tree node with left child
	void rotateWithLeftChild(AvlNode * & k2){
		AvlNode *k1 = k2->left; //make k1 point to the X
		k2->left = k1->right; //make the left of k2 point to Z
		k1->right = k2; //make the right of k1 point to k2
		k2->height = max(height(k2->left), height(k2->right)) + 1; //make the height of k2, the highest of either
		k1->height = max(height(k1->left), k2->height) + 1; //make the height of k1, the highest of either
		k2 = k1;
	}

	//do same as above but with right child. 
	void rotateWithRightChild(AvlNode * & k3){
		AvlNode *k4 = k3->right; //make k4 point to X
		k3->right = k4->left; //make the right of k3 point to Y
		k4->left = k3; //make the left of k4 point to k3
		k3->height = max(height(k3->left), height(k3->right)) + 1; //make the height of k3, the highest of either
		k4->height = max(height(k4->right), k3->height) + 1; //make the height of k4, the highest of either
		k3 = k4;
	}

	// doubles rotate binary tree node: first left child, with its right child, then k3 with left child.
	void doubleWithLeftChild(AvlNode * & k3){
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	//same as above but with first right child.
	void doubleWithRightChild(AvlNode * & k4){
		rotateWithLeftChild(k4->right);
		rotateWithRightChild(k4);
	}

	//to take out things from the subtree. the x is the input to remove, the t is the root.
	//makes the new root
	void remove(const Comparable & x, AvlNode * & t){
		if(t == nullptr)
		    return;   // Item not found; do nothing

		if(x < t->element)
		    remove(x, t->left);
		else if(t->element < x)
		    remove(x, t->right);
		else if(t->left != nullptr && t->right != nullptr) // Two children
		{
		    t->element = findMin(t->right)->element;
		    remove(t->element, t->right);
		}
		else
		{
		    AvlNode *oldNode = t;
		    t = (t->left != nullptr) ? t->left : t->right;
		    delete oldNode;
		}
		balance(t);
	}

	//to insert things into the tree. the x is the input, the t is the root.
	//makes a new binarynode, which is the new root if there isn't one
	//keeps moving left or right, depending on what the oder of input, since its recursive function.
	void insert(Comparable && x, AvlNode * & t){
		if(t == nullptr){
		    t = new AvlNode{std::move(x), nullptr, nullptr};
		}
		else if(x < t->element){
		    insert(std::move(x), t->left);
		}
		else if(t->element < x){
		    insert(std::move(x), t->right);
		}
		else{
		    ;  // Duplicate; do nothing
		}
	}
	
   	//find smallest item in tree
	AvlNode * findMin(AvlNode *t) const{
		if(t == nullptr)
		    return nullptr;
		if(t->left == nullptr)
		    return t;
		return findMin(t->left);
	}

	//find biggest item in tree
	AvlNode * findMax(AvlNode *t) const{
		if(t != nullptr)
		    while(t->right != nullptr)
			t = t->right;
		return t;
	}

    	//to find the item in the tree, the x is the input and the t is the root.
	bool contains(const Comparable & x, AvlNode *t) const{
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
	void makeEmpty(AvlNode * & t){
		if(t != nullptr){
		    makeEmpty(t->left);
		    makeEmpty(t->right);
		    delete t;
		}
		t = nullptr;
	}

	//to make a copy of the tree
	AvlNode * clone(AvlNode *t) const{
	if(t == nullptr)
	    return nullptr;
	else
	    return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
	}
  	//to print the tree
	void printTree(AvlNode *t) const{
		if(t != nullptr){
		    printTree(t->left);
		    cout << t->element << "\n";
		    printTree(t->right);
		}
	}

	// to find the left height subtree
	int leftheight(AvlNode *t){
		if(t == nullptr){
			return -1;
		}
		else{
			return height(t->left);
		}
	}
	// to find the right height subtree
	int rightheight(AvlNode *t){
		if(t == nullptr){
			return -1;
		}
		else{
			return height(t->right);
		}
	}
	};

#endif /* BINARYSEARCHTREE_H_ */

