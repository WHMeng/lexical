#include "BinaryTree.h"

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
		if(pt->_lchild) preorder(pt->_lchild);
		if(pt->_rchild) preorder(pt->_rchild);
	}
}

template <typename elemType>
void BinaryTree<elemType>::
inorder(BTnode<elemType> *pt, ostream &os) const{
	if(pt){
		display_val(pt, os);
		if(pt->_lchild) inorder(pt->_lchild);
		if(pt->_rchild) inorder(pt->_rchild);
	}
}

template <typename elemType>
void BinaryTree<elemType>::
postorder(BTnode<elemType> *pt, ostream &os) const{
	if(pt){
		display_val(pt, os);
		if(pt->_lchild) postorder(pt->_lchild);
		if(pt->_rchild) postorder(pt->_rchild);
	}
}
