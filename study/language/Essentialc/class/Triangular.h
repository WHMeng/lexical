#ifndef TRIANGULAR_H
#define TRIANGULAR_H

#include <string>
#include <vector>
#include <iostream>
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
	Triangular(int len = 1, int bp = 1);
	int length() const {return _length;}
	int beg_pos() const {return _beg_pos;}
	int elem(int pos) const;

	bool next(int &val) const;
	void next_reset() const {_next = _beg_pos - 1;}
	Triangular &copy(const Triangular &rhs);
	static int size() {return _elems.size();}
	static bool is_elem(int value);
	static void gen_elements(int length);
	static void gen_elems_to_value(int value);
	static void display(int length, int beg_pos, ostream &os=cout);
	friend int operator * (const Triangular_iterator &rhs);
	friend void Triangular_iterator::check_integrity() const;
	friend ostream & operator << (ostream &os, const Triangular &rhs);
private:
	int _length;
	int _beg_pos;
	mutable int _next;
	static vector<int> _elems;
	static const int _buf_size = 1024;
	static const int _max_elems = 1024;
	int _buffer[_buf_size];
};

class iterator_overflow{
public:
	iterator_overflow(int index, int max)
		: _index(index), _max(max){}
	int index() {return _index;}
	int max() {return _max;}
	void what_happened(ostream &os = cerr){
		os << "internal error: current index "
			<< _index << " exceeds maximum bound: "
			<< _max;
	}
private:
	int _index;
	int _max;
};

#endif
