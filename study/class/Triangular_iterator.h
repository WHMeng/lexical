#ifndef TRIANGULAR_ITERATOR_H
#define TRIANGULAR_ITERATOR_H

class Triangular_iterator{
public:
	Triangular_iterator(int index)
		:_index(index-1){}
	bool operator == (const Triangular_iterator &) const;
	bool operator != (const Triangular_iterator &) const;
	//int operator * () const;
	void check_integrity() const;
	friend int operator * (const Triangular_iterator &rhs);
	Triangular_iterator &operator ++(); // «∞÷√ ++
	Triangular_iterator operator ++(int); // ∫Û÷√ ++
private:
	int _index;
};

inline bool Triangular_iterator::
operator == (const Triangular_iterator &rhs) const{
	return _index == rhs._index;
}

inline bool Triangular_iterator::
operator != (const Triangular_iterator &rhs) const{
	return !(*this == rhs);
}

inline Triangular_iterator &Triangular_iterator::
operator ++ (){
	++_index;
	check_integrity();
	return *this;
}

inline Triangular_iterator Triangular_iterator::
operator ++ (int){
	Triangular_iterator tmp = *this;
	++_index;
	check_integrity();
	return tmp;
}

#endif
