#include "Fibonacci.h"

vector<int> Fibonacci::_elems;

void Fibonacci::
gen_elems(int pos) const{
	if(_elems.empty()){
		_relems.push_back(1);
		_relems.push_back(1);
	}
	int ix = _elems.size();
	int n2 = _elems[ix-1];
	int n1 = _elems[ix-2];
	while(ix < pos){
		int elem = n1 + n2;
		_elems.push_back(elem);
		n1 = n2;
		n2 = elem;
		ix++;
	}
}
