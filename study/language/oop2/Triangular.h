#ifndef TRIANGULAR_H
#define TRIANGULAR_H

#include "num_sequence.h"

class Triangular : public num_sequence{
public:
	Triangular();
protected:
	virtual void gen_elems(int pos) const;
	static vector<int> _elems;
};

inline Triangular::
Triangular()
: num_sequence(_elems)
{
}

#endif
