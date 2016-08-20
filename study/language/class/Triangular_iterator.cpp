#include "Triangular_iterator.h"
#include "Triangular.h"

#if 0
int Triangular_iterator::
operator * () const{
	check_integrity();
	return Triangular::_elems[_index];
}
#endif

int
operator * (const Triangular_iterator &rhs){
	rhs.check_integrity();
	return Triangular::_elems[rhs._index];
}

void Triangular_iterator::
check_integrity() const{
#if 1
	if(_index >= Triangular::_max_elems){
		iterator_overflow ex(_index, Triangular::_max_elems);
		throw ex;
	}
#endif
	if(_index >= Triangular::_elems.size())
		Triangular::gen_elements(_index+1);
}




