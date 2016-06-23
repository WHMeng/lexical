#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
using namespace std;

template <typename Type>
class BTnode;

template <typename elemType>
class BinaryTree{
public:
	BinaryTree();
	BinaryTree(const BinaryTree &);
	~BinaryTree();
	BinaryTree& operator = (const BinaryTree &);
	void insert(const elemType &elem);
	void remove(const elemType &elem);
	void preorder(ostream &os = cout){preorder(_root, os);}
	void inorder(ostream &os = cout){inorder(_root, os);}
	void postorder(ostream &os = cout){postorder(_root, os);}
	bool empty() {return _root == 0;}
	void clear(){
		if(_root){
			clear(_root);
			_root = 0;
		}
	}
private:
	BTnode<elemType> *_root;
	void copy(BTnode<elemType> *tar, BTnode<elemType> *src);
	void clear(BTnode<elemType> *pt);
	void remove_root();
	void preorder(BTnode<elemType> *pt, ostream &os) const;
	void inorder(BTnode<elemType> *pt, ostream &os) const;
	void postorder(BTnode<elemType> *pt, ostream &os) const;
	void display_val(BTnode<elemType> *pt, ostream &os);
};

template <typename elemType>
inline BinaryTree<elemType>::
BinaryTree()
: _root(0)
{}

template <typename elemType>
inline BinaryTree<elemType>::
BinaryTree(const BinaryTree &rhs){
	copy(_root, rhs._root);
}

template <typename elemType>
inline BinaryTree<elemType>::
~BinaryTree(){
	clear();
}

template <typename elemType>
inline BinaryTree<elemType>&
BinaryTree<elemType>::
operator = (const BinaryTree &rhs){
	if(this != &rhs){
		clear();
		copy(_root, rhs._root);
	}
	return *this;
}

template <typename elemType>
inline void
BinaryTree<elemType>::
insert(const elemType &elem){
	if(!_root)
		_root = new BTnode<elemType>(elem);
	else
		_root->insert_value(elem);
}

template <typename elemType>
inline void
BinaryTree<elemType>::
remove(const elemType &elem){
	if(_root){
		if(_root->val == elem)
			remove_root();
		else
			_root->remove_value(elem, _root);
	}
}

template <typename elemType>
inline void
BinaryTree<elemType>::
display_val(BTnode<elemType> *pt, ostream &os){
	os << pt->_val << ' ';
}

#endif
