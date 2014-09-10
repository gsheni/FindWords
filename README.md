FindWords
=========

This program will seart through a text file and using a search tree, notify you if the word exists in the text file or not. 

This was done by first creating a Binary Search Tree (BST) and an Adelson-Velskii and Landis' (AVL) tree. 
The Binary Search Tree tree was modified to contain the height of each node in the tree, similar to the AVL tree.
The BST class and the AVL class contain a method called printHeight that prints the heights of the tree, as well as that of the root's left and right subtrees.

For example, its output for the Binary Search Tree class could be: 
“Tree Height: 30 (Left Subtree: 29) (Right Subtree: 24)”, if both left and right subtrees exist.

In order to test these two classes, a FindWords program was written. The FindWords program is expected to read in a two command line argument 
