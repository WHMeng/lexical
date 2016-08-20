#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
using namespace std;

// 函数对象实现我们原本可能以独立函数加以定义的事物
// 主要是为了效率，我们可以令 call 运算符成为 inline
// 因而消除“通过函数指针来调用函数”时需付出的额外代价
//
// 标准库定义一组函数对象 头文件 functional
// --6 个算数运算：plus<type> minus<type> negate<type>
// --multiplies<type> divides<type> modules<type>
//
// --6 个关系：less<type>, less_equal<type>, greater<type>
// --greater_equal<type>, equal_to<type>, not_equal_to<type>
//
// --3 个逻辑运算(分别对应&&，||，！)：
// --logical_and<type>, logical_or<type>, logical_not<type>
//
// transform(fib.begin(), fib.end(),
//			 pell.begin(),
//			 fib_plus_pell.begin(),
//			 plus<int>());
// )

// 二元转一元（函数对象配接器 Adapters）
// 绑定配接器：
// bin1st 会将指定值绑定至第一操作数
// bin2nd 会将指定值绑定至第二操作数

// 逆转函数对象的真伪
// not1 可逆转一元函数对象的真伪
// not2 可逆转二元函数对象的真伪
// example: 找出所有大于或等于 10 的元素
// while((iter = find_if(iter, vec.end(),
//									not1(bind2nd(less<int>, 10))))
//								!= vec.end())

// insertion adapters（插入配接器）
// --back_inserter() 会以容器的 push_back() 函数取代 = 运算符，如：
//		vector<int> result_vec;
//		unique_copy(ivec.begin(), ivec.end(),
//					back_inserter(result_vec));
//
// --inserter() 会以容器的 insert() 函数取代 = 运算符，如：
//		vector<int> svec_res;
//		unique_copy(svec.begin(), svec.end(),
//					inserter(svec_rec, svec_res.end()));
//
// --front_inserter() 会以容器的 push_front() 函数取代 = 运算符，
// 只适用于 list 和 deque； 如：
//		list<int> ilist_clone;
//		copy(ilist.begin(), ilist.end(),
//					front_inserter(ilist_clone));

bool less_than(int v1, int v2){
	return v1 < v2 ? true : false;
}

bool greater_than(int v1, int v2){
	return v1 > v2 ? true : false;
}

vector<int> less_then_10(const vector<int> &vec){
	vector<int> nvec;
	for(int i = 0; i < vec.size(); ++i)
		if(vec[i] < 10)
			nvec.push_back(vec[i]);
	return nvec;
}

// 函数指针
vector<int> filter_ver1(const vector<int> &vec,
		int filter_value, bool (*pred)(int, int)){
	vector<int> nvec;
	for(int i = 0; i < vec.size(); ++i){
		if(pred(vec[i], filter_value))
			nvec.push_back(vec[i]);
	}
	return nvec;
}

// 函数对象+配接器
vector<int> filter_ver2(const vector<int> &vec, 
		int val, less<int> lt){ // 无法引用传递函数对象？
	vector<int> nvec;
	vector<int>::const_iterator iter = vec.begin();
	while((iter = find_if(iter, vec.end(),
					bind2nd(lt, val))) != vec.end()){
		nvec.push_back(*iter);
		iter++;
	}
	return nvec;
}

// 函数对象+配接器（泛型）
template <typename InputIterator, typename OutputIterator,
		 typename ElemType, typename Comp>
OutputIterator
filter(InputIterator first, InputIterator last,
		OutputIterator at, const ElemType &val, Comp pred){
	while((first = find_if(first, last,
					bind2nd(pred, val))) != last){
		*at++ = *first++;
	}
	return at;
}

// vector 输出
template <typename elemType>
void display(const vector<elemType> &vec, ostream &os = cout){
#if 0
	// 为何这段不行？
	vector<elemType>::const_iterator beg_it = vec.begin();
	vector<elemType>::const_iterator end_it = vec.end();
#endif
	const int *beg_it = &vec[0];
	const int *end_it = &vec[vec.size()];
	os << "seq:";
	for(; beg_it != end_it; ++beg_it)
		os << ' ' << *beg_it;
	os << endl;
}

// 泛型输出
template <typename Iterator>
void display(Iterator first, Iterator last, ostream &os = cout){
	os << "seq:";
	while(first != last){
		os << ' ' << *first;
		first++;
	}
	os << endl;
}

void test_filter_ver(){
	const int elem_size = 8;
	int ia[elem_size] = {12, 8, 43, 0, 6, 21, 3, 7};
	vector<int> ivec(ia, ia+elem_size);
	vector<int> ivec2 = filter_ver2(ivec, 8, less<int>());
	display(ivec2);
}

void test_filter(){
	const int elem_size = 8;
	int ia[elem_size] = {12, 8, 43, 0, 6, 21, 3, 7};
	vector<int> ivec(ia, ia+elem_size);

	int ia2[elem_size];
	vector<int> ivec2(elem_size);
	vector<int> ivec3;

	int *ia2_end = filter(ia, ia+elem_size, ia2, 8, less<int>());
	display(ia2, ia2_end);

	vector<int>::iterator ivec2_end = filter(ivec.begin(), ivec.end(),
			ivec2.begin(), 8, greater<int>());
	display(ivec2.begin(), ivec2_end);

#if 1
	vector<int>::iterator ivec3_end = filter(ivec.begin(), ivec.end(),
			back_inserter(ivec3), 8, greater<int>()); // back_inserter 无法通过编译？
	display(ivec3.begin(), ivec3_end);
#endif
}

template <typename Iterator1, typename Iterator2>
Iterator2 mycopy(Iterator1 first, Iterator1 last, Iterator2 at){
	while(first != last){
		*at++ = *first++;
	}
	return at;
}

int main()
{
	const int elem_size = 8;
	int ia[elem_size] = {12, 8, 43, 0, 6, 21, 3, 7};
	vector<int> ivec;
	mycopy(ia, ia+elem_size, back_inserter(ivec));
	display(ivec);
	//test_filter();
	return 0;
}
