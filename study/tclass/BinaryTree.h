#ifndef BINARYTREE_H
#define BINARYTREE_H

template <typename elemType>
class BinaryTree{
public:
	BinaryTree();
	BinaryTree(const BinaryTree &);
	~BinaryTree();
	BinaryTree& operator = (const BinaryTree);
	bool empty() {return _root == 0;}
	void clear();
private:
	BTnode<elemType> *_root;
	void copy(BTnode<elemType> *tar, BTnode<elemType> *src);
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

#endif
