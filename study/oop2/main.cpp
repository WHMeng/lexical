#include "num_sequence.h"
#include "Fibonacci.h"
#include "Triangular.h"

int main(){
	const int pos = 8;
	Fibonacci fbi;
	Triangular tri;

	display(cout, fbi, pos);
	cout << endl;

	display(cout, fbi);
	cout << endl;

	display(cout, tri, pos);
	cout << endl;

	display(cout, tri);
	cout << endl;

	return 0;
}
