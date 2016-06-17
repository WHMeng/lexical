#ifndef TRIANGULAR_H
#define TRIANGULAR_H

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include "Triangular_iterator.h"
using namespace std;

class Triangular{
public:
	typedef Triangular_iterator iterator;
	Triangular_iterator begin() const{
		return Triangular_iterator(_beg_pos);
	}
	Triangular_iterator end() const{
		return Triangular_iterator(_beg_pos+_length);
	}
	Triangular();
	Triangular(int len);
	Triangular(int len = 1, int bp = 1);
	int length() const {return _length;}
	int beg_pos() const {return _beg_pos;}
	int elem(int pos) const;

	bool next(int &val) const;
	void next_reset() const {_next = _beg_pos - 1;}
	Triangular &Triangular::copy(const Triangular &rhs);
	static bool is_elem(int value);
	static void gen_elements(int length);
	static void gen_elems_to_value(int value);
	static void display(int length, int beg_pos, ostream &os = cout);
private:
	int _length;
	int _beg_pos;
	mutable int _next;
	static vector<int> _elems;
	static const int _buf_size = 1024;
	static const int _max_elems = 1024;
	int _buffer[_buf_size];
};

#endif
