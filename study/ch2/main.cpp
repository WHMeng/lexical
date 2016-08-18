#include "NumSeq.h"

int main()
{
	// seq_ptr 是一个指针；指针指向的是一个函数，
	// 函数含有一个 int 类型参数，函数的返回值为
	// 指向 vector<int> 类型的指针，指针指向的内容为只读
	const vector<int> * (*seq_ptr)(int) = 0; // 函数指针
	int elem;

	seq_ptr = seq_array[ns_catal];
	seq_elem(15, elem, seq_ptr);
	display_message("val: ", elem);

	display_message('\n');

	seq_ptr = seq_array[ns_fibon];
	seq_elem(15, elem, seq_ptr);
	display_message("val: ", elem);
	return 0;
}
