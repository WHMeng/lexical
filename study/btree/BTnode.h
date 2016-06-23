#ifndef BTNODE_H
#define BTNODE_H

template <typename Type>
class BinaryTree;

template <typename valType>
class BTnode{
public:
	BTnode(const valType &val);
	void insert_value(const valType &val);
	void lchild_leaf(BTnode *leaf, BTnode *subtree);
	void remove_value(const valType &val, BTnode *& prev);
	friend class BinaryTree<valType>;
private:
	valType _val;
	int _cnt;
	BTnode *_lchild;
	BTnode *_rchild;
};

template <typename valType>
inline BTnode<valType>::
BTnode(const valType &val)
: _val(val)
{
	_cnt = 1;
	_lchild = _rchild = 0;
}


#endif

