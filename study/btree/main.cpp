#include "BinaryTree.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	BinaryTree<string> bt;
	bt.insert("Piglet");
	bt.insert("Eeyore");
	bt.insert("Roo");
	bt.insert("Tigger");
	bt.insert("Chris");
	bt.insert("Pooh");
	bt.insert("Kanga");

	bt.inorder();
	cout << endl;

	bt.remove("Piglet");

	bt.preorder();
	cout << endl;

	bt.remove("Pooh");

	bt.preorder();
	cout << endl;

	bt.remove("Roo");

	bt.preorder();
	cout << endl;

	bt.remove("Eeyore");

	bt.preorder();
	cout << endl;

	bt.remove("Tigger");

	bt.preorder();
	cout << endl;

	bt.remove("Chris");

	bt.preorder();
	cout << endl;

	bt.remove("Kanga");

	bt.preorder();
	cout << endl;
	return 0;
}
