#if 0

重载操作符与转换
======================

不能重载的操作符：
:: .* . ?:

一般将算术和关系操作符定义为非成员函数，而将赋值操作符定义为成员函数

操作符定义为非成员函数时，通常必须将它们设置为操作类的友元

cout << item1 + item2 << endl 等效于
cout << operator+(item1, item2)

item1 += item2 等效于
item1.operator+=(item2)

选择成员或非成员实现
======================

1）= [] () -> 等操作符必须定义为成员，否则出现编译错误
2）复合赋值操作符通常应定义为类的成员，但不强制这样做
3）改变对象状态或与给定类型紧密联系的其他一些操作符，如 ++ -- * 等，通常定义为类成员
4）对称的操作符，如算术、相等、关系、位操作符，最好定义为普通非成员函数

重载 << 和 >> 操作符
============================

为了与 IO 标准一致，操作符应接受 ostream& 作为第一个形参，对类型 const 对象的引用作为
第二个形参，并返回对 ostream 形参的引用

ostream& operator<<(ostream &os, const ClassType &obj){
	// any special logic to prepare obj
	// actual output of members
	os << // ...
	// return ostream obj
	return os;
}

IO 操作符必须为非成员函数，否则左操作数只能是该类类型的对象，就会出现这样的奇怪写法：

ClassType item;
item << cout;

既定义了算术操作符又定义了相关复合赋值操作符的类，一般应使用复合赋值操作符实现算术操作符

类定义下标操作符时，一般需要定义两个版本：
1）非 const 成员并返回引用
2）const 成员并返回 const 引用
===============================================

class Foo{
public:
	int &operator[] (const size_t);
	const int &operator[] (const size_t) const;
	//...
private:
	vector<int> data;
	//...
};

int &Foo::operator[] (const size_t index){
	return data[index];
}

const int &Foo::operator[] (const size_t index) const{
	return data[index];
}

成员访问操作符
==================

-> 必须定义为类成员函数，* 不要求定义为成员，但一般定义为成员

#endif

























