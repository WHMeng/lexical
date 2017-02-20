#if 0

key word: 类作用域、数据隐藏、构造函数；
		  友元、使用隐藏的 this 指针、静态(static)、可变(mutable) 成员

具体类 pair

数据抽象和封装两个重要优点：
1. 避免类内部出现无意的、可能破坏对象状态的用户级错误
2. 随时间推移可以根据需求改变或缺陷报告来完美类实现，而无须改变用户级代码

---------------------------------------------------------------------------------

class Screen {
public:
	// interface member functions
private:
	std::string contents;
	std::string::size_type cursor;
	std::string::size_type height, width;
};

使用类型别名来简化类
=====================

class Screen {
public:
	// interface member functions
	typedef std::string::size_type index;
private:
	std::string contents;
	index cursor;
	index height, width;
};

定义重载成员函数
=====================

class Screen {
public:
	// interface member functions
	typedef std::string::size_type index;
	char get() const {return contents[cursor];}
	char get(index ht, index wd) const;
private:
	std::string contents;
	index cursor;
	index height, width;
};

显式指定 inline 成员函数(inline 成员函数的定义必须在调用该函数的每个源文件中是可见的)
========================================================================================

class Screen {
public:
	// interface member functions
	typedef std::string::size_type index;
	char get() const {return contents[cursor];}
	inline char get(index ht, index wd) const;
	index get_cursor() const;
private:
	std::string contents;
	index cursor;
	index height, width;
};

char Screen::get(index r, index c) const{
	index row = r * width;
	return contents[row+c];
}

inline Screen::index Screen::get_cursor() const{
	return cursor;
}

何时使用 this 指针
=====================

当我们需要將一个对象作为整体引用而不是引用对象的一个成员时，必须显式引用 this


class Screen {
public:
	Screen & move(index r, index c);
	Screen & set(char);
	Screen & set(index, index, char);
	// other members as before
};

Screen & Screen::set(char c){
	contents[cursor] = c;
	return *this;
}

Screen & Screen::move(index r, index c){
	index row = r * width;
	cursor = row + c;
	return *this;
}

然后可以这样用:

Screen screen;
// ...
screen.move(4, 0).set('#');

从 const 成员函数返回 *this
============================

const 成员函数只能返回 *this 作为一个 const 引用

class Screen {
public:
	Screen & display(std::ostream &os)
					{do_display(os); return *this;}
	const Screen & display(std::ostream &os) const
					{do_display(os); return *this;}
private:
	void do_display(std::ostream &os) const
					{os << contents;}
	// as before
};

Screen screen(5, 3);
const Screen blank(5, 3);
screen.set('#').display(cout); // calls nonconst version
blank.display(cout); // calls const version

可变数据成员
===============

class Screen {
public:
private:
	// 使用 access_ctr 来跟踪调用 Screen 成员函数的频繁程度
	mutable size_t access_ctr; // may change in a const members
	// as before
};

void Screen::do_display(std::ostream &os) const{
	++access_ctr;
	os << contents;
}

类作用域
=============

int height;

class Screen {
public:
	void dummy_fcn(index height){
		cursor = width * height; // 使用参数 height
		cursor = width * this->height; // 使用类成员 height
		cursor = width * Screen::height; // 使用类成员 height
		cursor = width * ::height; // 使用全局 height
	}
private:
	index cursor;
	index height, width;
};

构造函数
==========

构造函数不能声明为 const

没有默认构造函数的类类型的成员，以及 const 或引用类型的成员，
不管是哪种类型，都必须在构造函数初始化列表中进行初始化

成员被初始化的次序就是定义成员的次序

class X {
	int i;
	int j;
public:
	// run-time error: i is initialized before j
	X(int val): j(val), i(j) {}
};

隐式类类型转换
=================

explicit 关键字只能用于类内部的构造函数声明上，在类的定义外部
所做的定义上不要再重复它

通常，除非有明显的理由想要定义隐式转换，否则，单形参构造函数应该为 explicit。
將构造函数设置为 explicit 可以避免错误，并且当转换有用时，用户可以显式的构造
对象

友元
========

友元声明可以出现在类中的任何地方(通常將友元声明成组地放在类定义的开始或结尾)

友元可以是普通的非成员函数，或前面定义的其他类的成员函数，或整个类

友元声明將已命名的类或非成员函数引入到外围作用域中。此外，友元函数可以在类的
内部定义，该函数的作用域扩展到包围该类定义的作用域

class X {
	friend class Y;
	friend void f() {// ok to define freind function in the class body}
};

class Z {
	Y *ymem; // ok: declaration for class Y introduced by friend in X
	void g() {return ::f();} // ok: declaration of f introduced by X
};

static 类成员
==============

使用 static 成员而不是全局对象有 3 个优点
1. static 成员的名字是在类的作用域中，因此可以避免与其他类的成员或全局
   对象名字冲突
2. 可以实施封装。static 成员可以是私有成员，而全局对象不可以
3. 通过阅读程序容易看出 static 成员是与特定类关联的

class Account {
public:
	void applyint() {amount += amount * interestRate;}
	static double rate() {return interestRate;}
	static void rate(double); // set a new rate
private:
	std::string owner;
	double amount;
	static double interestRate;
	static double initRate();
};

当在类外部定义 static 成员时，无须重复指定 static 保留字

void Account::rate(double newRate){
	interestRate = newRate;
}

因为 static 成员不是任何对象的组成部分，所以 static 成员函数不能被声明为 const。毕竟
，將成员函数声明为 const 就是承诺不会修改该函数所属的对象。最后，static 成员函数也不
能被声明为虚函数

static 数据成员必须在类定义体的外部定义(正好一次)

double Account::interestRate = initRate();

一旦成员名出现，static 成员就是在类作用域中。因此，我们可以没有限定的直接使用名为
initRate 的 static 成员函数，作为 interestRate 初始化式。注意，尽管 initRate 是私
有的，我们仍然可以使用该函数来初始化 interestRate。像任意的其他成员定义一样，
interestRate 的定义是在类的作用域中，因此可以访问该类的私有成员

只要初始化式是一个常量表达式，整型 const static 数据成员就可以在类的定义体中进行初始化

class Account {
public:
	static double rate() {return interestRate;}
	static void rate(double); // set a new rate
private:
	static const int period = 30; // interest posted every 30 days
	double daily_tbl[period]; // ok: period is constant expression
};

const int Account::period;

const static 数据成员在类的定义体中初始化时，该数据成员仍必须在类的定义体外进行定义，
在类内部提供初始化式时，成员的定义不必再指定初始值

class Bar {
public:
	// ...
private:
	static Bar mem1; // ok
	Bar *mem2;		 // ok
	Bar mem3;		 // error
};

class A {
	int f(int n = a); // error
	int g(int n = b); // ok
	int a;
	static int b;
};

#endif
