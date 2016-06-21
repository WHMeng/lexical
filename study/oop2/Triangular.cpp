#include "Triangular.h"

vector<int> Triangular::_elems;

void Triangular::
gen_elems(int pos) const{
	int ix = _elems.size();
	while(++ix <= pos){
		_elems.push_back(ix*(ix+1)/2);
	}
}
