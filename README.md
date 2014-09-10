FindWords
=========

This program will seart through a text file and using a search tree, notify you if the word exists in the text file or not. 

This was done by first creating a Binary Search Tree (BST) and an Adelson-Velskii and Landis' (AVL) tree. 
The Binary Search Tree tree was modified to contain the height of each node in the tree, similar to the AVL tree.
The BST class and the AVL class contain a method called printHeight that prints the heights of the tree, as well as that of the root's left and right subtrees.

For example, its output for the Binary Search Tree class could be: 
“Tree Height: 30 (Left Subtree: 29) (Right Subtree: 24)”, if both left and right subtrees exist.

In order to test these two classes, a FindWords program was written. The FindWords program will read in a two command line arguments, the first corresponds to te file name ("vocab.nytimes.random.txt"), and the second corresponds to the type of class to use ("BST" or "AVL"). The program will open the file, and insert every word into a Binary Search Tree or an AVL tree. 

Each line must only contain a single word. 
The program does two things:
- Outputs the height of the tree created. 
- Ask for a word to look for in the tree.

To exit, simply enter the word "sortie"
