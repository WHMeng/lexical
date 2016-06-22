#ifndef NUM_SEQUENCE_H
#define NUM_SEQUENCE_H

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

class num_sequence {
public:
    typedef vector<unsigned int>::iterator iterator;
	
	virtual ~num_sequence(){};
	virtual num_sequence *clone() const = 0;

	unsigned int elem( int pos ) const;
	bool is_elem(  unsigned int ) const;
	int  pos_elem( unsigned int ) const;	

    const char* what_am_i() const;
	static  int max_elems(){ return _max_elems; }
	ostream& print( ostream &os = cout ) const; 
	
	int length()  const { return _length;  }
    int beg_pos() const { return _beg_pos; }

	iterator begin() const 
		 { return _relems.begin()+_beg_pos-1; }

	iterator end() const 
		 { return _relems.begin()+_beg_pos+_length; }

	void set_position( int pos );
	void set_length( int pos );

	bool operator ==( const num_sequence& ) const;
    bool operator !=( const num_sequence& ) const;
	
    const vector<unsigned int>* sequence() const
		{ return &_relems; }

protected:
    // static const int    _max_elems = 1024;	
	// for compilers not supporting const static
	enum { _max_elems = 1024 };
	
	virtual void gen_elems( int pos ) const = 0;
	int _calc_pos( unsigned int elem ) const;
	bool check_integrity( int pos, int size ) const;

	num_sequence( int, int, vector<unsigned int>& );

	int _length; 	
    int _beg_pos;  
	vector< unsigned int> &_relems;
};


inline bool num_sequence::
operator==( const num_sequence &rhs ) const 
{
	return ( _beg_pos == rhs._beg_pos ) &&
		   ( _length  == rhs._length );
}

inline bool num_sequence::
operator !=( const num_sequence &rhs ) const 
	{ return ! ( *this == rhs ); }

inline void num_sequence::
set_position( int pos )
{
	if ( pos <= 0 || pos > _max_elems ){
		 cerr << "!! invalid position: " << pos 
			  << " setting pos to default value of 1\n"
			  << "If inadequate, invoke set_position(pos)\n";
		 pos = 1;
	}
	_beg_pos = pos;
}

inline void num_sequence::
set_length( int len )
{
	if ( len <= 0 || len + _beg_pos - 1 > _max_elems ){
		 cerr << "!! invalid length for this object: " << len 
			  << " setting length to default value of 1\n"
			  << "If inadequate, invoke set_length(len)\n";
	     len = 1;
	}
	_length = len;
}

inline num_sequence::
num_sequence( int beg_pos, int len, 
			  vector< unsigned int> &re ) : _relems( re )
{ 
	set_position( beg_pos ); 
	set_length( len ); 
}

inline unsigned int num_sequence::
elem( int pos ) const 
{
	return ( ! check_integrity( pos, _relems.size() ))
		     ? 0 : _relems[ pos-1 ];
}

#include <typeinfo>

inline const char* num_sequence::
what_am_i() const 
{
    return typeid( *this ).name();
}

inline void 
display( ostream &os, const num_sequence &ns, 
		 int pos, int elem_val )
{
	os << "The element at position " << pos 
	   << " for the "
	   << ns.what_am_i() 
	   << " sequence is " << elem_val << endl;
}

inline void 
display( ostream &os, const num_sequence &ns, int pos )
{
	os << "The element at position " 
	   << pos            << " for the "
	   << ns.what_am_i() << " sequence is " 
	   << ns.elem( pos ) << endl;
}

inline bool num_sequence::
check_integrity( int pos, int size ) const
{
	bool status = true;

	if ( pos <= 0 || pos > _max_elems ){
		 cerr << "!! invalid position: " << pos
			  << " Cannot honor request\n";
		 status = false;
	}
    else if ( pos > size )
		      gen_elems( pos );

	return status;
}

// is_elem() returns true if the element passed in a valid element 
// in the object's sequence. For example, if the object represents 
// a fibonacci sequence { 1,1, 2, 3, 5, 8, 13, 21, 34, 45}, beginning 
// as position 3 for a length of 2, then
//    Obj.is_elem( 1 ); // false
//    Obj.is_elem( 3 ); // true
//    Obj.is_elem( 5 ); // false
//    Obj.is_elem( 4 ); // false

inline bool num_sequence::
is_elem( unsigned int elem ) const
{
	return ( ! check_integrity( _beg_pos, _length ))
		     ? false : binary_search( begin(), end(), elem );
}

// pos_elem() returns the position of an element within the sequence 
// independent of what the object's position and length. The object 
// simply is used to identify the sequence for which to return a position. 
// If the element value is invalid, return 0. For example, if the object 
// represents a fibonacci sequence, then
//     Obj.pos_elem( 1 ); // returns 1 - ignore duplicate
//     Obj.pos_elem( 32 ); // returns 9
//     Obj.pos_elem( very-large-instance ); // your choice
//     Obj.pos_elem( 4 ); // return 0

#endif
