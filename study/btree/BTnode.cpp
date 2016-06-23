#include "BTnode.h"

template <typename valType>
void BTnode<valType>::
insert_value(const valType &val){
	if(val == _val){
		_cnt++;
		return;
	}
	if(val < _val){
		if(!_lchild)
			_lchild = new BTnode(val);
		else
			_lchild->insert_value(val);
	}
	else{
		if(!_rchild)
			_rchild = new BTnode(val);
		else
			_rchild->insert_value(val);
	}
}

template <typename valType>
void BTnode<valType>::
lchild_leaf(BTnode *leaf, BTnode *subtree){
	while(subtree->_lchild)
		subtree = subtree->_lchild;
	subtree->_lchild = leaf;
}

template <typename valType>
void BTnode<valType>::
remove_value(const valType &val, BTnode *& prev){
	if(val < _val){
		if(!_lchild)
			return;
		else
			_lchild->remove_value(val, _lchild);
	}
	else if(val > _val){
		if(!_rchild)
			return;
		else _rchild->remove_value(val, _rchild);
	}
	else{
		if(_rchild){
			prev = _rchild;
			if(_lchild){
				if(!prev->_lchild)
					prev->_lchild = _lchild;
				else
					BTnode<valType>::lchild_leaf(_lchild, prev->_lchild);
			}
		}
		else
			prev = _lchild;
		delete this;
	}
}


