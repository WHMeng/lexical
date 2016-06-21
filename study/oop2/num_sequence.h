#ifndef NUM_SEQUENCE_H
#define NUM_SEQUENCE_H

#include <vector>
#include <iostream>
#include <typeinfo>
using namespace std;

class num_sequence;
ostream & operator << (ostream &os, const num_sequence &ns);

class num_sequence{
public:
	int elem(int pos) const;
	const char *who_am_i() const;
	ostream &print(ostream &os = cout) const;
protected:
	virtual void gen_elems(int pos) const = 0;
	bool check(int pos) const;
	vector<int> &_relems;
	num_sequence(vector<int>&);
	static const int _max_size = 1024;
};

inline num_sequence::
num_sequence(vector<int> &re)
: _relems(re)
{
}

inline void
display(ostream &os, num_sequence &ns, int pos){
	cout << ns.who_am_i() << ": "
		<< ns.elem(pos);
}

inline void
display(ostream &os, num_sequence &ns){
	cout << ns.who_am_i() << ":"
		<< ns << endl;
}

inline bool num_sequence::
check(int pos) const{
	if(pos < 0 || pos >= _max_size)
		return false;
	if(pos > _relems.size())
		gen_elems(pos);
	return true;
}

inline int num_sequence:: 
elem(int pos) const{
	return check(pos) ? _relems[pos-1] : -1;
}

inline const char *num_sequence::
who_am_i() const{
	return typeid(*this).name();
}

#endif
