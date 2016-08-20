#include "num_sequence.h"

ostream & operator << (ostream &os, const num_sequence &ns){
	return ns.print(os);
}

ostream &num_sequence::
print(ostream &os) const{
	int ix = 0;
	int end = _relems.size(); 
	while(ix < end){
		os << ' ' << _relems[ix];
		ix++;
	}
	return os;
}
