#include "num_sequence.h"

ostream& 
operator<<( ostream &os, const num_sequence &ns )
{  
    return ns.print( os );
}

// base class non-inline implementations
// normally would go in a program text file: .cpp

ostream& num_sequence::
print( ostream &os ) const
{
		
	int elem_pos = _beg_pos-1;
	int end_pos = elem_pos + _length;

    if ( ! check_integrity( end_pos, _relems.size() ))
			 return os;

     os << "( "
	    << _beg_pos << " , "
	    << _length << " ) ";
   
	while ( elem_pos < end_pos )
		     os << _relems[ elem_pos++ ] << ' ';

	return os;
}

int num_sequence::
pos_elem( unsigned int elem ) const
{
	cout << "pos_elem( " << elem << " )\n";

	if ( _relems[ _relems.size()-1 ] < elem )
		 return _calc_pos( elem );

	iterator iter = find( _relems.begin(), _relems.end(), elem );
	return ( iter == _relems.end() )
		     ? 0 
			 : distance( _relems.begin(), iter )+1;
}

int num_sequence::
_calc_pos( unsigned int elem ) const
{
    // presumption is that check_integrity() has passed
	int pos = _relems.size()-1;

    cout << "calc_pos invoked()!: elem: " << elem 
		 << " pos: " << pos 
		 << " at: "  << _relems[ pos ] 
		 << "\n";

	while (( pos < _max_elems ) && 
		   ( _relems[ pos ] < elem ))
	{
		   gen_elems( ++pos ); // virtual call!
		   cout << " pos: " << pos 
		        << " at: "  << _relems[ pos ] << endl;
	}

	return (( pos < _max_elems ) && 
		   ( _relems[pos] == elem )) ? pos+1 : 0;
}
