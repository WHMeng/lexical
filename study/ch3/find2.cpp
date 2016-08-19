#include <iostream>
#include <vector>
#include <list>
using namespace std;

// 所有容器类（以及 string 类）的共通操作
// == != =
// empty()
// size()
// clear()
// begin() end()
// insert() erase()
// --iterator insert(iterator pos, elemType val)
// --在 pos 之前插入 val
//
// --void insert(iterator pos, int count, elemType val)
// --在 pos 之前插入 count 个 val
//
// --void insert(iterator1 pos, iterator2 first, iterator2 last)
// --在 pos 之前插入 [first, last) 的各个元素
//
// --iterator insert(iterator pos)
// --在 pos 之前插入所属型别的默认值
//
// --iterator erase(iterator pos)
// --抹除 pos 所指的元素
//
// --iterator erase(iterator first, iterator last)
// --抹除 [first, last) 所指的元素
//
// list 不支持 iterator 的偏移运算
//
// 序列容器
// vector
// list
// deque

template <typename IteratorType, typename elemType>
IteratorType
find(IteratorType first, IteratorType last,
		const elemType &value){
	for(; first != last; ++first)
		if(value == *first)
			return first;
	return last;
}

int main()
{
	const int asize = 8;
	int ia[asize] = {1, 1, 2, 3, 5, 8, 13, 21};
	vector<int> ivec(ia, ia+asize);
	list<int> ilist(ia, ia+asize);

	int *pia = find(ia, ia+asize, 13);
	if(pia != ia+asize)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	vector<int>::iterator it;
	it = find(ivec.begin(), ivec.end(), 1);
	if(it != ivec.end())
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	list<int>::iterator iter;
	iter = find(ilist.begin(), ilist.end(), 13);
	if(iter != ilist.end())
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	return 0;
}
