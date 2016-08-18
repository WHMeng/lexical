#ifndef NUMSEQ_H
#define NUMSEQ_H
#include <iostream>
#include <vector>
using namespace std;

// 1）重载函数参数表必须相同，返回值的类型不足以区分不同的重载函数
// 2）默认参数列表只能放在参数表最后，可以放在声明，也可以放在定义
//	  但不能两处都放
void display_message(char ch, ostream &out=cout);
void display_message(const string &msg, ostream &out=cout); // 默认参数是否需要参数名？
void display_message(const string &msg, int val, ostream &out=cout);
const vector<int> *fibon_seq(int size);
const vector<int> *catal_seq(int size);
bool seq_elem(int pos, int &elem,const vector<int>* (*seq_ptr)(int));

enum ns_type {ns_fibon, ns_catal};
// const 对象只在本文件可见
const int seq_cnt = 2;
// 下面这个并不是 const 对象
extern const vector<int> * (*seq_array[seq_cnt])(int); // 指针数组

// 注意模板的声明与定义
template <typename elemType>
void display_message(const string &msg, const vector<elemType> &vec, ostream &out=cout){
	out << msg;
	for(int i = 0; i < vec.size(); ++i){
		elemType t = vec[i];
		out << ' ' << t;
	}
	out << endl;
}

// 多文件中内联函数的定义要放在头文件中
inline bool is_size_ok(int size){
	const int max_size = 1024;
	string msg("too large: ");
	if(size <= 0 || size >= max_size){
		display_message(msg, size);
	}
	return true;
}


#endif
