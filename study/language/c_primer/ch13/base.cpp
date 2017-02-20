#if 0

复制控制
==============

类特殊成员函数：复制构造函数、赋值操作符和析构函数

有一种特别常见的情况需要类定义自己的复制控制成员：类具有指针成员

复制构造函数
==============

只有单个形参，而且该形参是对本类类型对象的引用(常用 const 修饰)，可用于：

1. 根据另一个同类型的对象显式或隐式初始化一个对象
2. 复制一个对象，将它作为实参传给一个函数
3. 从函数返回时复制一个对象
4. 初始化顺序容器中的元素
5. 根据元素初始化式列表初始化数组元素

string null_book = "9-9999-99999-9"; // copy-initialization
string dots(10, '.'); // direct-initialization

string empty_copy = string(); // copy-initialization
string empty_direct; // direct-initialization

ifstream file1("filename"); // ok: direct initialization
ifstream file2 = "filename"; // error: copy constructor is private

// this initialization is okey only if the Sales_item(const string &) constructor is not explicit
Sales_item item = string("9-99-9999-9");

vector<string> svec(5);

编译器首先使用 string 默认构造函数创建一个临时值来初始化 svec，然后使用复制构造函数將临时
值复制到 svec 的每个元素

Sales_item primer_eds[] = {
	string(0-201-1324-7),
	string(0-201-5644-8),
	string(0-201-9884-9),
	Sales_item()
};

Point global;

Point foo_bar(Point arg){
	Point local = arg;
	Point *heap = new Point(global);
	*heap = local;
	Point pa[4] = {local, *heap};
	return *heap;
}

合成复制构造函数
======================

1. 直接复制内置类型成员的值
2. 类类型成员使用该类的复制构造函数进行复制
3. 复制数组时合成复制构造函数將复制数组的每一个元素

合成复制构造函数的简单理解

class Sales_item {
// ...
private:
	std::string isbn;
	int units_sold;
	double revenue;
};

Sales_item::Sales_item(const Sales_item &orig)
	: isbn(orig.isbn),
	, units_sold(orig.units_sold),
	, revenue(orig.revenue)
	{}

禁止复制
===============

为了防止复制，类必须显式声明其复制构造函数为 private
然而，类的友元和成员仍可以进行复制。如果想要连友元和成员中的复制也禁止，
就可以声明一个(private)复制构造函数但不对其定义

声明而不定义成员函数是合法的，但是，使用未定义成员的任何尝试將导致链接失败。
通过声明(但不定义) private 复制构造函数，可以禁止任何复制类类型对象的尝试：
用户代码中尝试將在编译时标记为错误，而成员函数和友元中的复制尝试将在链接时
导致错误


赋值操作符
============




#endif
