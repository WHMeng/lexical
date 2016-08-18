#include "NumSeq.h"

const vector<int> * (*seq_array[])(int) = { // 指针数组
	fibon_seq, catal_seq
};

void display_message(char ch, ostream &out){
	out << ch;
}

void display_message(const string &msg, ostream &out){
	out << msg;
}

void display_message(const string &msg, int val, ostream &out){
	out << msg;
	out << val << endl;
}

// 计算 fibonacci 中的第 size 个元素，
// 并返回含有这些元素的静态容器的地址
const vector<int> *
fibon_seq(int size){
	static vector<int> elems;
	if(!is_size_ok(size))
		return 0;
	for(int i = elems.size(); i < size; ++i){
		if(i == 0 || i == 1)
			elems.push_back(1);
		else
			elems.push_back(elems[i-1]+elems[i-2]);
	}
	return &elems;
}

const vector<int> *
catal_seq(int size){
	static vector<int> elems;
	if(!is_size_ok(size))
		return 0;
	for(int i = elems.size(); i < size; ++i){
		if(i == 0 || i == 1)
			elems.push_back(1);
		else{
			int ans = 0;
			for(int j = 0; j < i; ++j)
				ans += elems[j]*elems[i-1-j];
			elems.push_back(ans);
		}
	}
	return &elems;
}

// 返回数列中位置为 pos 的元素
bool seq_elem(int pos, int &elem,
		const vector<int>* (*seq_ptr)(int)){
	if(!seq_ptr)
		display_message("Internal Error: seq_ptr is set to null!\n");
	const vector<int> *pseq = seq_ptr(pos);
	if(!pseq){
		elem = 0;
		return false;
	}
	display_message("seq:", *pseq);
	elem = (*pseq)[pos-1];
	return true;
}
