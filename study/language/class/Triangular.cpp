#include <algorithm>
#include "Triangular.h"

vector<int> Triangular::_elems;

int Triangular::
elem(int pos) const{
	return _elems[pos-1];
}

Triangular::
Triangular(){
	_length = 1;
	_beg_pos = 1;
	_next = 0;
}

Triangular::
Triangular(int len, int bp)
:	_length(len > 0 ? len : 1),
	_beg_pos(bp > 0 ? bp : 1)
{
	_next = bp - 1;
	int elem_cnt = _beg_pos + _length - 1;
	if(_elems.size() < elem_cnt)
		gen_elements(elem_cnt);
}

bool Triangular::
next(int &value) const{
	if(_next < _beg_pos + _length - 1){
		value = _elems[_next++];
		return true;
	}
	return false;
}

void Triangular::
gen_elements(int length)
{
	if(length < 0 || length > _max_elems){
		cerr << "length too large" << endl;
		return;
	}
	if(_elems.size() < length){
		int ix = _elems.size() ? _elems.size()+1 : 1;
		for(; ix <= length; ++ix)
			_elems.push_back(ix*(ix+1)/2);
	}
}

void Triangular::
gen_elems_to_value(int value)
{
	int ix = _elems.size();
	if(!ix){
		_elems.push_back(1);
		ix = 1;
	}
	while(_elems[ix-1] < value && ix < _max_elems){
		++ix;
		_elems.push_back(ix*(ix+1)/2);
	}
	if(ix == _max_elems)
		cerr << "Triangular Sequence: oops: value too large "
			<< value << " -- exceeds max size of "
			<< _max_elems << endl;
}

int sum(const Triangular &trian){
	if(!trian.length())
		return 0;
	int val, sum = 0;
	trian.next_reset();
	while(trian.next(val))
		sum += val;
	return sum;
}

bool Triangular::
is_elem(int value){
	if(!_elems.size() ||
			_elems[_elems.size()-1] < value)
		gen_elems_to_value(value);
	vector<int>::iterator found_it;
	vector<int>::iterator end_it = _elems.end();
	found_it = find(_elems.begin(), end_it, value);
	return found_it != end_it;
}

Triangular &Triangular::
copy(const Triangular &rhs){
	if(this != &rhs){
		_length = rhs._length;
		_beg_pos = rhs._beg_pos;
		_next = rhs._beg_pos - 1;
	}
	return *this;
}

ostream & operator << (ostream &os, const Triangular &rhs){
	os << "( " << rhs.beg_pos() << ", " << rhs.length() << " )";
	rhs.display(rhs.length(), rhs.beg_pos(), os);
	return os;
}

void Triangular::
display(int length, int beg_pos, ostream &os){
	int elem_cnt = beg_pos + length - 1;
	if(_elems.size() < elem_cnt)
		gen_elements(elem_cnt);
	for(int i = beg_pos-1; i < elem_cnt; i++)
		os << ' ' << _elems[i];
#if 0
	next_reset();
	int val;
	while(next(val))
		os << ' ' << val;
#endif
}
