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


#endif
