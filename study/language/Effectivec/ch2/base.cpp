// 
// -----------------------------------------------------------------------
// (5) 了解 C++ 默默编写并调用哪些函数
//     Know what function C++ silently writes and calls
//
//     一个空类被 C++ 处理过后：
//     如果自己没声明，编译器会为它声明一个 copy 构造函数、一个
//     copy assignment 操作符和一个析构函数、一个 default 构造函数
//     这些都是 public 且 inline 的
//
//     class Empty(){};
//
//     就像：
//
//     class Empty(){
//	   public:
//	       Empty(){...}
//	       Empty(const Empty &rhs){...}
//	       ~Empty(){...} // non-virtual (除非 base class 自身声明有 virtual)
//	       Empty &operator=(const Empty &rhs){...}
//     };
//     
//     唯有当这些函数被调用，它们才会被编译器创建出来。
//
// ----------------------------------------------------------------------
// (6) 若不想使用编译器自动生成的函数，就该明确拒绝
//     Explicitly disallow the use of compiler-generated functions you do
//     not want
//
//     为驳回编译器自动提供的机能，可将相应的成员函数声明为 private 并且
//     不予实现。但当不慎在 member 函数或 friend 函数之内调用它们，连接器
//     会抱怨
//
//     因此另一个方法是把相应的成员函数声明为 private 并不予实现，但是是在
//     base class 内
//
//     class Uncopyable{
//     protected:
//         Uncopyable(){}
//         ~Uncopyable(){}
//     private:
//         Uncopyable(const Uncopyable&);
//         Uncopyable &operator=(const Uncopyable&);
//     };
//
//     class HomeForSale : private Uncopyable{
//     ...
//     };
//
// ----------------------------------------------------------------------
// (7) 为多态基类声明 virtual 析构函数
//     Declare destructors virtual in ploymorphic base classes
//
//     带多态性质的 base classes 应该声明一个 virtual 析构函数。如果 class
//     带有任何 virtual 函数，它就应该拥有一个 virtual 析构函数
//
//     --使用基类指针指向派生类对象问题
//
//     classes 的设计目的如果不是作为 base clases 使用，或不是为了具备多态
//     性，就不应该声明 virtual 析构函数
//
//     class Point{
//     public:
//         Point(int xCoord, int yCoord);
//         ~Point();
//         // virtual ~Point();
//     private:
//         int x, y;
//     };
//
//     sizeof(Point) == 8
//
//     但如果使用 virtual 函数，对象必须携带某些信息，主要用来在运行期决定
//     哪个 virtual 函数该被调用。这份信息通常是由一个 vptr(virtual table
//     pointer) 指针指出。vptr 指向一个由函数指针构成的数组，称为 vtbl
//     (virtual table)；每个带有 virtual 函数的 class 都有一个对应的 vtbl。
//     当对象调用某一 virtual 函数，实际被调用的函数取决于该对象的 vptr 所
//     指的那个 vtbl
//
// -----------------------------------------------------------------------
// (8) 别让异常逃离析构函数
//     Prevent exceptions from leaving destructors
//
//     -- 待补充
//
// -----------------------------------------------------------------------
// (9) 绝不在构造和析构过程中调用 virtual 函数
//     Never call virtual functions during construction or destruction
//
// -----------------------------------------------------------------------
// (10) 令 operator= 返回一个 reference to *this
//      Have assignment perators return a reference to *this
//
//      int x, y, z;
//      x = y = z = 15;
//
//      由连锁形式得：
//
//      x = (y = (z = 15));
//
//      为了实现“连锁赋值”，赋值操作符必须返回一个 reference 指向操作符的
//      左侧实参
//
//      这也适用于所有赋值相关运算(+= -=)等等，而且，这只是个协议，并无
//      强制性
//
// -----------------------------------------------------------------------
// (11) 在 operator= 中处理“自我赋值”
//      Handle assignment to self in operator=
//
//      class Bitmap(){...};
//      class Widget{
//			...
//		private:
//			Bitmap *pb;
//      };
//
//      Widget &
//      Widget::operator=(const Widget &rhs){
//			// if(this == &rhs) // 如果是自我赋值，就不做任何事
//			// return *this;
//			delete pb;
//			pb = new Bitmap(*rhs.pb);
//			return *this;
//      }
//
//      上面有异常安全问题，下面则可避免
//
//      Widget &
//      Widget::operator=(const Widget &rhs){
//			Bitmap *pOrig = pb;
//			pb = new Bitmap(*rhs.pb);
//			delete pOrig;
//			return *this;
//      }
//
// ------------------------------------------------------------------------
// (12) 复制对象时勿忘其每一个成分
//      Copy all parts of an object
//
