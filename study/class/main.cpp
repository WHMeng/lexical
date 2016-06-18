#include "Triangular.h"
#include "Triangular_iterator.h"
using namespace std;

int main()
{
	Triangular tri(10);
	Triangular::iterator it = tri.begin();
	Triangular::iterator end_it = tri.end();
	cout << "Triangular Series of " << tri.length() << endl;
	cout << tri << endl;
	while(it != end_it){
		cout << *it << ' ';
		++it;
	}
	cout << endl;
	return 0;
}
