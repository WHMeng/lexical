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

重载操作符
============

操作符函数有一个返回值和一个形参表。形参表必须具有与该操作符数目相同的形参
(如果操作符是一个类成员，则包括隐式 this 形参)。赋值是二元运算，所以该操作符
函数有两个形参：第一个形参对应左操作数，第二个形参对应右操作数

当操作符作为成员函数时，它的第一个操作隐式绑定到 this 指针。有些操作符(包括赋值操作符)
必须是定义自己的类的成员。因为赋值必须是类的成员，所以 this 绑定到指向左操作数的指针。
因此，赋值操作符接受单个形参，且该形参是同一类类型的对象

赋值操作符的返回类型应该与内置类型赋值运算返回的类型相同。内置类型的赋值运算返回对
右操作数的引用，因此，赋值操作符也返回对同一类类型的引用

class Sales_item {
public:
	// ...
	Sales_item & operator=(const Sales_item &);
};

Sales_item 的合成赋值操作符可能如下：

Sales_item &Sales_item::operator=(const Sales_item &rhs){
	isbn = rhs.isbn; // calls string::operator=
	units_sold = rhs.units_sold;
	revenue = rhs.revenue;
	return *this;
}


析构函数
============

撤销一个容器(不管是标准库容器还是内置数组)时，也会运行容器中的类类型元素的析构函数
容器中的元素总是按逆序撤销：首先撤销下标为 size() - 1 的元素，然后 ... 最后是撤销
下标为 [0] 的元素

三法则
=======

如果类需要析构函数，则它也需要赋值操作符和复制构造函数

合成析构函数并不删除指针成员所指向的对象

即使我们编写了自己的析构函数，合成析构函数仍然运行

class Sales_item {
public:
	// ...
	~Sales_item(){}
	// as before
};

撤销 Sales_item 类型的对象时，將运行这个什么也不做的析构函数，它执行完毕后，
将会运行合成析构函数以撤销类的成员，合成析构函数调用 string 析构函数来撤销
string 成员，string 析构函数释放了保存 isbn 的内存


c++ 类管理指针成员的常用方法
================================

1. 指针成员采取常规指针型行为。这样的类具有指针的所有缺陷但无需特殊的复制控制
2. 类可以实现所谓的“智能指针”行为。指针所指向的对象是共享的，但类能够防止悬垂指针
3. 类采取值型行为。指针所指向的对象是唯一的，由每个类对象独立管理

方法一：

class HasPtr{
public:
	HasPtr(int *p, int i) : ptr(p), val(i) {}
	int *get_ptr() const {return ptr;}
	int get_int() const {return val;}
	void set_ptr(int *p) {ptr = p;}
	void set_int(int i) {val = i;}
	int get_ptr_val() const {return *ptr;}
	void set_ptr_val(int v) const {*ptr = v;}
private:
	int *ptr;
	int val;
};

int obj = 0;
HasPtr ptr1(&obj, 42); // int* member points to obj, val is 42
HasPtr ptr2(ptr1); // int* member points to obj, val is 42

方法二：

class U_Ptr{
	friend class HasPtr;
	int *ip;
	size_t use;
	U_Ptr(int *p) : ip(p), use(1) {}
	~U_Ptr() {delete ip;}
};

class HasPtr{
public:
	HasPtr(int *p, int i) : ptr(new U_Ptr(p), val(i)) {}
	HasPtr(const HasPtr &orig)
		: ptr(orig.ptr)
		, val(orig.val){
			++ptr->use;
		}
	HasPtr & operator=(const HasPtr &);
	~HasPtr() {
		if(--ptr->use == 0) delete ptr;
	}
	int *get_ptr() const {return ptr->ip;}
	int get_int() const {return val;}
	void set_ptr(int *p) {ptr->ip = p;}
	void set_int(int i) {val = i;}
	int get_ptr_val() const {return *ptr->ip;}
	void set_ptr_val(int i) {*ptr->ip = i;}
private:
	U_Ptr *ptr;
	int val;
};

HasPtr &HasPtr::operator=(const HasPtr &rhs){
	++rhs.ptr->use;
	if(--ptr->use == 0)
		delete ptr;
	ptr = rhs.ptr;
	val = rhs.val;
	return *this;
}

定义值型类
============

class HasPtr{
public:
	HasPtr(const int &p, int i) : ptr(new int(p), val(i)) {}
	HasPtr(const HasPtr &orig)
		: ptr(new int(*orig.ptr))
		, val(orig.val) {}
	HasPtr &operator=(const HasPtr &);
	~HasPtr() {delete ptr;}
	int *get_ptr() const {return ptr;}
	int get_int() const {return val;}
	void set_ptr(int *p) {ptr = p;}
	void set_int(int i) {val = i;}
	int get_ptr_val() const {return *ptr;}
	void set_ptr_val(int v) const {*ptr = v;}
};

HasPtr &HasPtr::operator=(const HasPtr &rhs){
	*ptr = *rhs.ptr;
	val = rhs.val;
	return *this;
}


#endif
