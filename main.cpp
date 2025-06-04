/*
  Binary Search Tree
  Created By: Ethan Chesire
  Last Updated 5/2/2025

  Code creates a double linked list tree that has commands. To add to if from a pre-created file or the console, to print out the tree in an easy to follow visual and to delete a node from the tree.
 */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//What is included in each node
class Node {
public:

  int value;
  Node* left;
  Node* right;
  Node* parent;


  int getValue() {
    return value;
  }
  
};

//Adding function
void add(Node*& root, Node* head, int in) {

  //For the start of a tree
  if (root == NULL) {
    Node* newNode = new Node();
    root = newNode;
    newNode->value = in;
  }

  //Adding on to the left or right
  else {
    if (in >= head->value) {

      if (head->right != NULL) {
	head = head->right;
	add(root, head, in);
      }
      else if (head->right == NULL) {
	Node* newNode = new Node();
	newNode->value = in;
	head->right = newNode;
	newNode->parent = head;
      }
      
    }
    else if (in < head->value) {

      if (head->left != NULL) {
        head = head->left;
        add(root, head, in);
      }
      else if (head->left == NULL) {
        Node* newNode = new Node();
        newNode->value = in;
        head->left = newNode;
	newNode->parent = head;
      }

    }
  }

}

//Print function to show the tree
void print(Node* head, int depth) {

  if (head->right != NULL){
    print(head->right, depth + 1);
  }

  for (int j = 0; j < depth; j++) {
    cout << '\t';
  }
  cout << head->value << endl;
    
  if (head->left != NULL) {
    print(head->left, depth + 1);
  }
}

//what is called after the number wanted to delete is found
void del(Node* head, int in, Node*& root) {
  //when there is no children
  if (head->right == NULL && head->left == NULL && head->value == in) {
    if (head->parent->right == head) {
      head->parent->right = NULL;
      head->parent = NULL;
    }
    else if (head->parent->left == head) {
      head->parent->left = NULL;
      head->parent = NULL;
    }
  }

  //A right child only
  else if (head->right != NULL && head->left == NULL && head != root) {
    if (head->parent->right == head) {
      head->parent->right = head->right;
      head->right->parent = head->parent;
      head = head->right;
    }
    else if (head->parent->left == head) {
      head->parent->left = head->right;
      head->right->parent = head->parent;
      head = head->right;
    }
  }

  //A right child only of the root
  else if (head->right != NULL && head->left == NULL && head == root) {
    root = head->right;
    head->right = NULL;
    root->parent = NULL;
    head = root;
  }

  //A left child only
  else if (head->left != NULL && head->right == NULL && head != root) {
    if (head->parent->right == head) {
      head->parent->right = head->left;
      head->left->parent = head->parent;
      head = head->left;
    }
    else if (head->parent->left == head) {
      head->parent->left = head->left;
      head->left->parent = head->parent;
      head = head->left;
    }

  }

  //A left child only of the root
  else if (head->left != NULL && head->right == NULL && head == root) {
    root = head->left;
    head->right = NULL;
    root->parent = NULL;
    head = root;
  }

  //Two children
  else if (head->right != NULL && head->left != NULL) {
    Node* temp = head->right;
    while (temp->left != NULL) {
      temp = temp->left;
    }
    head->value = temp->value;
    del(temp, temp->value, root);
  }
}

//To locate a node before deleting it
void find(Node* head, int in, Node*& root){
   if (in >= head->value) {

      if (head->right != NULL && head->value != in) {
        head = head->right;
        find(head, in, root);
      }
      
      else if (head->value == in) {
        del(head, in, root);
      }

      else if (head->right == NULL) {
	cout << "Data point was not found" << endl;
      }

    }
    else if (in < head->value) {

      if (head->left != NULL && head->value != in) {
        head = head->left;
        find(head, in, root);
      }

      else if (head->value == in) {
	del(head, in, root);
      }
      
      else if (head->left == NULL) {
        cout << "Data point was not found" << endl;
      }

    }
}

//The center piece
int main() {

  int depth = 0;
  int in = 0;
  char input[10];
  int amount = 0;
  bool working = true;
  Node* root = NULL;
  Node* head = NULL;

  cout << endl << "Welcome to Binaty Search Tree, please choose one of the following options..." << endl;

  //Continuous statements so you can use it for as long as you want
  while (working == true) {
    //Starting statement
    cout << endl << "ADD ... PRINT ... DELETE ... QUIT" << endl << " -  ";
    cin >> input;

    if (input[0] == 'A') {
      cout << "From the console or file?" << endl;
      cin >> input;

      if (input[0] == 'c') {
	cout << endl << "What is the value?" << endl;
	cin >> in;	
	add(root, head, in);
	head = root;
      }
      else if (input[0] == 'f') {
	cout << endl << "How many #'s should be added - ";
	cin >> amount;
	ifstream fin ("num.txt");
	for (int a = 0; a < amount; a++) {
	  fin >> in;
	  add(root, head, in);
	  head = root;
	}
	fin.close();
      }
    }
    
    else if (input[0] == 'P') {
      print(head, depth);
    }
        
    else if (input[0] == 'D') {
      cout << "What number do you want to delete from the tree?" << endl;
      cin >> in;
      find(head, in, root);
      cout << "DONE!" << endl;
      head = root;
    }
    
    else if (input[0] == 'Q') {
      cout << "Goodbye";
      working = false;
    }
    else {
      cout << "ERROR -- Try again" << endl; 
    }

  }
  
  return 0;
}
