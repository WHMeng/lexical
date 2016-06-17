#include <iostream>
#include <string>
#include <functional>
#include <vector>
using namespace std;

class Triangular{
public:
	Triangular(){
		_length = 1;
		_beg_pos = 1;
		_next = 0;
	};
	Triangular(int len);
	Triangular(int len, int bp){
		_length = len > 0 ? len : 1;
		_beg_pos = bp > 0 ? bp : 1;
		_next = _beg_pos - 1;
	};
	int length() const {return _length;}
	int beg_pos() const {return _beg_pos;}
	int elem(int pos) const;
	bool next(int &val);
	void next_reset(){_next = _beg_pos - 1;}
private:
	int _length;
	int _beg_pos;
	int _next;
	static vector<int> _elems;
};

int Triangular::elem(int &pos) const{
	return _elems[pos-1];
}

bool Triangular::next(int &value) const{
	if(_next < _beg_pos + _length - 1){
		value = _elems[_next++];
		return true;
	}
	return false;
}

int sum(const Triangular &trian){
	if(!trian.length())
		return 0;
	int val, sum = 0;
	trian.next_reset();
	while(trian.next(val))
		sum += val;
	return sum;
}

int main()
{
	return 0;
}


