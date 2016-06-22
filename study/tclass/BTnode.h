#ifndef BTNODE_H
#define BTNODE_H

template <typename Type>
class BinaryTree;

template <typename valType>
class BTnode{
public:
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

