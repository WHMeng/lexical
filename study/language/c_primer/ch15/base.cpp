//
// 面向对象编程基于三个基本概念：数据抽象、继承、动态绑定
//
// 动态绑定使编译器能够在运行时决定是使用基类中定义的函数还是派生类中
// 定义的函数
//
// class Item_base{
// public:
//     string book() {...}
//     virtual double net_price() const {...}
// private:
//     string isbn;
// protected:
//     double price;
// };
//
// class Bulk_item : public Item_base{
// public:
//     double net_price() const {...} // 不强制使用保留字 virtual
// private:
//     size_t min_qty;
// };
//
// void print_total(ostream &os, const Item_base &item, size_t n){
//     os << item.book() << endl;
//     os << item.net_price() << endl;
// }
//
// C++ 中通过基类的引用或指针调用虚函数时，发生动态绑定；被调用的函数
// 是引用或指针所指对象的实际类型所定义
//
// 基类成员函数：
// --------------
//
// 除了构造函数之外，任意非 static 成员函数都可以是虚函数
// virtual 只在类内部的成员函数声明中出现，不能用在类定义体外部出现的函
// 数定义上
//
// protected：
// -----------
// 
// 1. 成员不能被该类的用户访问
// 2. 可被该类的派生类访问
// 3. 派生类只能通过派生类对象访问其基类的 protected 成员，派生类对其基类类型
// 对象的 protected 成员没有特殊访问权限
//
// void Bulk_item::memfun(const Bulk_item &d, const Item_base &b){
//     doubel ret = price; // ok, this->price
//     ret = d.price; // ok, d.price
//     ret = b.price; // error
// }
//
// 希望禁止派生类访问的成员应该设为 private，提供派生类实现所需操作或数据的
// 成员应设为 protected。即提供给派生类型的接口是 protected 成员和 public 成员的组合
//
// 派生类和虚函数：
// ----------------
//
// 派生类中虚函数的声明必须与基类中的定义方式完全匹配，但有一个例外：
// 返回对基类型的引用或指针的虚函数。
//
// Item_base 类可以定义返回 Item_base * 的虚函数，如果这样，Bulk_item 类中
// 定义的实例可以定义为返回 Item_base * 或 Bulk_item *
//
// 只有通过引用和指针的调用，虚函数才能在运行时确定
//
// 编译时确定非 virtual 调用
// --------------------------
//
// 不管传给 print_total 的实参的实际类型是什么，对 book 的调用在编译时
// 确定为调用 Item_base::book （即使 Bulk_item 定义了自己的 book 函数
// 版本，这个调用也会调用基类中的版本）
//
// 覆盖虚函数机制
// --------------
//
// Item_base *baseP = &derived;
// double d = baseP->Item_base::net_price(42); // 强制调用
//
// 只有成员函数中的代码才应该使用作用域操作符覆盖虚函数机制
//
// 派生类虚函数调用基类版本时，必须显式使用作用域操作符。如果派生类函数
// 忽略了这样做，则函数调用会在运行时确定并且将是一个自身调用，从而导致
// 无穷递归
//
// 公用、私有、和受保护继承
// -------------------------
//
// 如果基类成员为 public 或 protected，则派生类：
//
// public 继承：   基类的 public 成员为派生类的 public 成员，基类的 protected
//                 成员为派生类的 protected 成员
//
// protected 继承：基类的 public 和 potected 成员在派生类中为 protected
//
// private 继承：  基类的所有成员在派生类中为 private 成员
//
// 去除个别成员
// -------------
//
// 派生类可以恢复继承成员的访问级别，但不能使访问级别比基类中原来指定的
// 更严格或更宽松
//
// class Base{
// public:
//     size_t size() const {return n};
// protected:
//     size_t n;
// };
//
// class Derived : private Base{
// public:
//     using Base::size;
// protected:
//     using Base::n;
// };
//
// 使用命名空间恢复访问级别
//
// 默认继承保护级别
// -----------------
//
// struct 与 class 唯一不同就是默认成员保护级别和默认的派生保护级别
//
// struct 默认 public 继承，class 默认 private 继承
//
// class Base {...};
// struct D1 : Base {...}; // 默认 public 继承
// class D2 : Base {...}; // 默认 private 继承
//
// 友元关系与继承
// ----------------
//
// 基类或派生类可以使其他类或函数成为友元，友元可以访问类的 private 和 
// protected 数据
//
// 友元关系不能被继承，基类的友元对派生类的成员没有特殊访问权限。如果基
// 类被授予友元关系，则只有基类具有特殊访问权限，该基类的派生类不能访问
// 授予友元关系的类
//
// class Base{
//     friend class Frnd;
// protected:
//     int i;
// };
//
// // Frnd has no access to members in D1
// class D1 : public Base{
// protected:
//     int j;
// };
//
// class Frnd{
// public:
//     int mem(Base b) {return b.i;} // ok, Frnd is friend to Base
//     int mem(D1 d) {return d.i;} // error, friendship doesn't inherit
// };
//
// // Frnd has no access to members in Base
// class D2 : public Frnd{
// public:
//     int mem(Base b) {return b.i;} // error, friendship doesn't inherit
// };
//
// 转换与继承
// -----------
//
// 因为派生类对象也是基类对象，所以存在从派生类引用到基类引用的自动转换，
// 对指针也类似，反之不成立
//
// 对一个希望接受基类类型引用的函数，如果传入一个派生类对象，则效果是将
// 派生类对象转换为基类类型引用
// 对一个希望接受基类对象的函数，如果传入一个派生类对象，则效果是用派生类
// 对基类对象进行初始化和赋值
//
// 用派生类对象对基类对象进行初始化或赋值
// ----------------------------------------
//
// 基类一般（显式或隐式）定义自己的复制构造函数和赋值操作符，这些成员
// 接受一个形参，该形参是基类类型的（const）引用。因为存在从派生类引用
// 到基类引用的转换，这些复制控制成员可用于从派生类对象对基类对象进行
// 初始化或赋值
//
// Item_base item;
// Bulk_item bulk;
// Item_base item(bulk);
// item = bulk;
//
// Bulk_item 类对象调用 Item_base 类的复制构造函数或赋值操作符时，将发生
// 下列步骤：
// 1）Bulk_item 对象转换为 Item_base 引用
// 2）将该引用作为实参传给复制构造函数或赋值操作符
// 3）那些操作符使用 Bulk_item 的 Item_base 部分分别对调用构造函数或赋值
//    的 Item_base 对象的成员进行初始化或赋值
// 4）一旦操作符执行完毕，对象即为 Item_base，它包含Bulk_item 的 Item_base
//    部分的副本，但实参的 Bulk_item 部分被忽略
//
// 如果是 public 继承，则用户代码和后代类都可以使用派生类到基类的转换。
// 如果类是使用 private 或 protected 继承派生的，则用户代码不能将派生
// 类型对象转换为基类对象
//
// 基类到派生类的转换
// --------------------
//
// 基类到派生类的自动转换是不存在的
//
// Item_base base;
// Bulk_item *bulkP = &base; // error
// Bulk_item &bulkRef = base; // error
// Bulk_item bulk = base; // error
//
// Bulk_item bulk;
// Item_base *itemP = &bulk; // ok
// Bulk_item *bulkP = itemP; // error !!!
//
// 定义合成的派生类默认构造函数
// -----------------------------
//
// class Bulk_item : public Item_base{
// public:
//     Bulk_item : min_qty(0), discount(0.0) {}
//     ...
// };
//
// 运行这个构造函数的效果是，首先使用 Item_base 的默认构造函数初始化
// Item_base 部分，再初始化 Bulk_item 部分的成员并执行构造函数的函数体
//
// 派生类只能初始化直接基类
//
// 尊重基类接口
// -------------
//
// 派生类构造函数不能初始化基类的成员且不应该对基类成员赋值。如果那些成员
// 为 public 或 protected，派生类构造函数可以在构造函数体内给基类成员赋值，
// 但是，这样做会违反基类的接口。派生类应该通过使用基类构造函数尊重基类的
// 初始化意图，而不是在派生类构造函数函数体内对这些成员赋值
//
// 定义派生类复制构造函数
// -----------------------
//
// 如果派生类显式定义自己的复制构造函数或赋值操作符，则该定义将完全覆盖
// 默认定义。被继承类的复制构造函数和赋值操作符负责对基类成分以及类自己
// 的成员进行复制或赋值
//
// class Base {...};
// class Derived : public Base{
// public:
//     Derived(const Derived &d)
//     : Base(d) // 如果少了这句，Derived 类则用 Base 类的默认构造函数
//     {}           初始化 Base 类部分
// };
//
// 赋值操作符类似：
//
// Derived &Derived::operator=(const Derived &rhs){
//     if(this != &rhs){
//         Base::operaotr=(rhs);
//         ...
//     }
//     return *this;
// }
//
// 虚析构函数
// ------------
//
// 每个析构函数只负责清除自己类的成员
//
// class Base{
// public:
//     ~Base() {}
//     ...
// private:
//     string str;
// };
//
// class Derived : public Base{
// public:
//     ~Derived() {}
//     ....
// private:
//     double d;
// };
//
// Base *pb = new Base;
// delete pb; // ok
// pb = new Derived; // ok
// delete pb; // 将调用 ~Base()，编译器没有定义该行为的后果
//
// 所以应该把析构函数声明为 virtual
//
// 像其他虚函数一样，析构函数的虚函数性质都将被继承
//
// 如果在构造函数或析构函数中调用虚函数，则运行的是为构造函数或析构函数
// 自身类型定义的版本
//
// 名字冲突与继承
// -----------------
//
// 与基类成员同名的派生类成员将屏蔽对基类成员的直接访问
// 可以使用作用域操作符访问被屏蔽成员
//
// 重载函数
// ---------
//
// 如果派生重定义了重载函数，则通过派生类只能访问派生类中重定义的那些成员
// 可以使用 using 引入基类的函数，或者可以在对象中使用作用域操作符
//
// class Base{
// public:
//     virtual void func() {...} // 当然也可以不是 virtual 函数
//     ...
// };
//
// class Derived : public Base{
// public:
//     virtual void func(int x) {...}
//     // using Base::func;
//     ...
// };
//
// Derived d;
// Derived *pd = &d;
// pd->func(); // error，但把派生类中的注释去掉就 ok
// pd->func(4); // ok
// pd->Base::func(); // ok
//
// 容器与继承
// ------------
//
// multiset<Item_base> basket;
// Item_base base;
// Bulk_item bulk;
// basket.insert(base); // ok
// basket.insert(bulk); // ok, 但派生部分被切掉
//                      // 而且放入容器后，它将不再是派生类对象
// 
// 句柄类与继承
// --------------
//
//
//
//
