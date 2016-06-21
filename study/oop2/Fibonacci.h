#ifndef FIBONACCI_H
#define FIBONACCI_H

#include "num_sequence.h"

class Fibonacci : public num_sequence{
public:
	Fibonacci();
protected:
	virtual void gen_elems(int pos) const;
	static vector<int> _elems;
};

inline Fibonacci::
Fibonacci()
: num_sequence(_elems)
{
}

#endif
