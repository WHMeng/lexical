// 
// 类的前置声明使我们得以进行类指针的定义，或以此类作为数据类型
// 而定义实际的类对象或取用类的任何一个成员，都必须先定义类本身
// 类的所有成员函数必须在类主体内声明，在类主体内定义的函数被视为 inline
//
// ClassA a = 8; // 这将调用带有单一参数的构造函数
// ClassA a(); // 此行将 a 定义为一个参数表为空的函数，该函数返回 ClassA 对象
// ClassA a; // 将调用默认构造函数
// ------------------------------------------------------------------
//
// 默认成员逐一初始化：
// class ClassA{
// public:
//		ClassA():x(0), y(0), str(""){}
// private:
//		int x, y;
//		string str;
// };
//
// ClassA a1;
// ClassA a2 = a1;
//
// 上面这样没有问题，但下面：
// class ClassB{
// public:
//		ClassB(int _x, int _y):x(_x), y(_y){
//			pb = new double[x*y];
//		}
//		~ClassB(){delete [] pb;}
// private:
//		int x, y;
//		double *pb;
// };
//
//{
//		ClassB b1(4, 4);
//		// 调用构造函数，申请新空间
//		{
//			ClassB b2 = b1;
//			// 默认成员初始化，b2->pb == b1->pb；
//			// b2 调用析构函数释放 b2->pb 和 b1->pb 指向的空间
//		}
//		// b1 调用析构函数，此前空间已被释放，故此处造成严重错误
//}
// ------------------------------------------------------------------
//
// mutable （可变） 和 const（不变）
// 在成员函数参数表后标注 const 告知编译器这个成员函数不会更改类对象的值
// 凡是在类主体外定义的 const 成员函数，必须同时在声明和定义指定 const
//
// class ClassA{
// public:
//		A(int v):val(v){len = 1;}
//		int change_val()const{
//			val += 1;
//			return val;
//		}
// private:
//		int val;
//		int len;
// };
//
// int sum(const A &a){
//		return a.change_val();
// }
//
// 如果 change_val() 必须被定义为 const 而 val 必须要改变，则以上写法将
// 产生错误；一个可行的方法是把 val 的定义写成 mutable int val; 表示 val
// 的改变不会破坏类的常数性
// -------------------------------------------------------------------
// 
// 静态的类成员
// static data members 表示一份可共享的 members，它可以在同型的所有对象中
// 被存取。对类而言， static data members 只有唯一一份实体，因此，必须在
// 程序代码文件中提供其清楚的定义；这种定义很像全局的定义，唯一的差别是，其
// 名称前附上 class scope 运算符。如：
// class A{
// private:
//		static vector<int> elems;
// };
//
// // 以下放置在程序代码文件，如 a.cpp
// vector<int> A::elems;
//
// 静态成员函数
// static member function 只有在“不存取任何 non-static members” 的条件下
// 才能被声明为 static；在类主体外定义时不需重复加上 static
// --------------------------------------------------------------------
//
// 运算符重载
// 运算符函数看起来很像普通函数，唯一的区别是它不需指定名称，只需在运算符
// 符号之前加上 operator；如：
// bool operator==(const ClassA &a) const;
//
// 运算符重载规则：
// 1）不可引入新的运算符。除了.， .*， ::， ?: 4 个运算符，其它运算符都可
//	  以重载
// 2）运算符的操作数数目不可变。每个二元运算符都需要两个操作数，每个一元
//    运算符都需要恰好一个操作数
// 3）运算符的优先级不可变。
// 4）运算符函数的参数表中，必须至少有一个参数为 class 类型。也就是说，我们
//    无法为像指针之类的 non-class 类型，重新定义其原已存在的运算符，当然更
//    无法为它引进新运算符
//
// 自增运算符（注意是否返回引用）：
// 前置++：
// ClassA &ClassA::operator++(){
//		++val;
//		return *this;
// }
//
// 后置版的参数表原本也应该是空的，然而重载规则要求，参数表必须独一无二，因
// 此 C++ 的方法是，要求后置版得有一个 int 参数：
// 后置++：
// ClassA ClassA::operator++(int){
//		ClassA tmp = *this;
//		++val;
//		return tmp;
// }
// ------------------------------------------------------------------------
//
// 友元函数：
// 只要在某个函数的原型之前加上 friend，就可以将它声明为某个 class 的 friend。
// 这份声明可以出现在 class 定义式的任意位置，不受 public 或 private 的影响。
// ------------------------------------------------------------------------
//
// 将 iostream 运算符重载
// ostream &opreator<<(ostream &os, const ClassA &a){
//		os << a.val << endl;
//		return os;
// }
//
// // 调用
// ClassA a(8);
// cout << a;
//
// 为什么不把 output 运算符设计为一个 member function 呢？因为作为一个
// member function，其左侧操作数必须是隶属同一个 class 之下的对象，如果
// output 运算符被设计为 class member function，那么 class object 就必须
// 被置于 output 运算符的左侧：
//
// ClassA a(8);
// a << cout;
//
// 这种奇怪的形式必定对 class 用户造成困惑
// ----------------------------------------------------------------------
//
// 指向类成员函数的指针
// void (ClassA::*pm)(int) = 0;
// 可以通过 typedef 加以简化：
// typedef void (ClassA::*PtrType)(int);
// PtrType pm = 0;
// pm = &ClassA::get_val;
//
//
//
//
