#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 实现一个函数对象
// 所谓 function object 乃是一种“提供有 function call 运算符” 的 class
// 当编译器在编译过程遇到函数调用，例如：
// lt(ival)
// lt 可能是函数名称，可能是函数指针，也可能是一个提供了 function call
// 运算符的 function object。如果 lt 是个 class object，编译器便会在内部
// 将此句转换成：
// lt.operator(ival);

class LessThan{
public:
	LessThan(int _val) : val(_val){}
	int comp_val() const {return val;} // 基值的读取
	void comp_val(int nval){val = nval;} // 基值的写入
	bool operator()(int value) const;
private:
	int val;
};

inline bool LessThan::
operator()(int value) const{
	return value < val;
}

int count_less_than(const vector<int> &vec, int comp){
	LessThan lt(comp);
	int count = 0;
	for(int i = 0; i < vec.size(); i++)
		if(lt(vec[i]))
			++count;
	return count;
}

void print_less_than(const vector<int> &vec, 
		int comp, ostream &os = cout){
	LessThan lt(comp);
	vector<int>::const_iterator iter = vec.begin();
	vector<int>::const_iterator it_end = vec.end();
	os << "elements less than " << lt.comp_val() << endl;
	while((iter = find_if(iter, it_end, lt)) != it_end){ // 把函数对象当参数传入
		os << *iter << ' ';
		++iter;
	}
}

int main()
{
	int ia[16] = {17, 12, 44, 9, 18, 45, 6, 14,
				  23, 67, 9, 0, 27, 55, 8, 16};
	vector<int> vec(ia, ia+16);
	int comp_val = 20;
	cout << "Number of elements less than "
		 << comp_val << " are "
		 << count_less_than(vec, comp_val) << endl;
	print_less_than(vec, comp_val);
	return 0;
}
