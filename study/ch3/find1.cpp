#include <iostream>
#include <vector>
using namespace std;

#if 0
// 只针对某一向量
const int *find(const vector<int> &vec, int value){
	for(int i = 0; i < vec.size(); ++i)
		if(vec[i] == value)
			return &vec[i];
	return 0;
}
#endif

#if 0
// 针对向量
// elemType 必须定义 = 运算符
template <typename elemType>
const elemType *find(const vector<elemType> &vec, const elemType &value){
	for(int i = 0; i < vec.size(); ++i)
		if(vec[i] == value)
			return &vec[i];
	return 0;
}
#endif

#if 0
// 针对数组
template <typename elemType>
const elemType *find(const elemType *array, int size,
		const elemType &value){
	if(!array || size < 1)
		return 0;
	for(int i = 0; i < size; ++i)
		if(array[i] == value)
			return &array[i];
	return 0;
}
#endif

#if 1
// 向量与数组通用
template <typename elemType>
inline const elemType *begin(const vector<elemType> &vec){
	return vec.empty() ? 0 : &vec[0];
}

template <typename elemType>
inline const elemType *end(const vector<elemType> &vec){
	return vec.empty() ? 0 : &vec[vec.size()];
}

template <typename elemType>
const elemType *find(const elemType *first, const elemType *last,
		const elemType &value){
	if(!first || !last)
		return 0;
	for(; first != last; ++first)
		if(*first == value)
			return first;
	return 0;
}
#endif

int main()
{
	int ia[8] = {1, 1, 4, 3, 5, 6, 17, 9};
	vector<int> va(ia, ia+8);
	double da[6] = {4.0, 1.0, 15.0, 6.0, 9.0, 7.0};
	string sa[4] = {"apple", "hello", "pear", "eye"};
	const int *pi = find(ia, ia+8, ia[3]);
	const int *pv = find(begin(va), end(va), va[3]);
	const double *pd = find(da, da+6, da[3]);
	const string *ps = find(sa, sa+8, sa[3]);
	cout << *pi << endl;
	cout << *pv << endl;
	cout << *pd << endl;
	cout << *ps << endl;
	return 0;
}
