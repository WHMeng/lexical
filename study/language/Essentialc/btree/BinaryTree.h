#include "BTnode.h"
#include <iostream>
using namespace std;

template <typename elemType>
class BinaryTree{
public:
	BinaryTree();
	~BinaryTree();
	BinaryTree(const BinaryTree &);
	BinaryTree& operator = (const BinaryTree &);
	friend ostream & operator << (ostream &os,
			const BinaryTree<elemType> &bt);
	void insert(const elemType &elem);
	void remove(const elemType &elem);
	void preorder(ostream &os = cout){preorder(_root, os);}
	void inorder(ostream &os = cout){inorder(_root, os);}
	void postorder(ostream &os = cout){postorder(_root, os);}
	bool empty(){return _root == 0;}
	void clear(){if(_root){clear(_root); _root = 0;}}
private:
	BTnode<elemType> *_root;
	void clear(BTnode<elemType> *pt);
	void copy(BTnode<elemType> *tar, BTnode<elemType> *src);
	void remove_root();
	void preorder(BTnode<elemType> *pt, ostream &os) const;
	void inorder(BTnode<elemType> *pt, ostream &os) const;
	void postorder(BTnode<elemType> *pt, ostream &os) const;
	void display_val(BTnode<elemType> *pt, ostream &os) const;
};

template <typename elemType>
inline ostream &
operator << (ostream &os, const BinaryTree<elemType> &bt){
	os << "Tree: " << endl;
	bt.print(os);
	return os;
}

template <typename elemType>
void BinaryTree<elemType>::
clear(BTnode<elemType> *pt){
	if(pt){
		clear(pt->_lchild);
		clear(pt->_rchild);
		delete pt;
	}
}

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
		if(_root->_val == elem)
			remove_root();
		else
			_root->remove_value(elem, _root);
	}
}

template <typename elemType>
inline void
BinaryTree<elemType>::
display_val(BTnode<elemType> *pt, ostream &os) const{
	os << pt->_val << ' ';
}

template <typename elemType>
void BinaryTree<elemType>::
remove_root(){
	if(!_root) return;
	BTnode<elemType> *tmp = _root;
	if(_root->_rchild){
		_root = _root->_rchild;
		if(tmp->_lchild){
			BTnode<elemType> *lc = tmp->_lchild;
			BTnode<elemType> *newlc = _root->_lchild;
			if(!newlc)
				_root->_lchild = lc;
			else
				BTnode<elemType>::lchild_leaf(lc, newlc);
		}
	}
	else 
		_root = _root->_lchild;
	delete tmp;
}

template <typename elemType>
void BinaryTree<elemType>::
preorder(BTnode<elemType> *pt, ostream &os) const{
	if(pt){
		display_val(pt, os);
		if(pt->_lchild) preorder(pt->_lchild, os);
		if(pt->_rchild) preorder(pt->_rchild, os);
	}
}

template <typename elemType>
void BinaryTree<elemType>::
inorder(BTnode<elemType> *pt, ostream &os) const{
	if(pt){
		if(pt->_lchild) inorder(pt->_lchild, os);
		display_val(pt, os);
		if(pt->_rchild) inorder(pt->_rchild, os);
	}
}

template <typename elemType>
void BinaryTree<elemType>::
postorder(BTnode<elemType> *pt, ostream &os) const{
	if(pt){
		if(pt->_lchild) postorder(pt->_lchild, os);
		if(pt->_rchild) postorder(pt->_rchild, os);
		display_val(pt, os);
	}
}
