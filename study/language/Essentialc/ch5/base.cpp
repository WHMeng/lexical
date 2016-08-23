//
// 继承（inheritance）
// 使我们得以将一群相关的类组织起来，并让我们得以分享其间的共通数据和操作行为
//
// 多态（polymorphism）
//
// 抽象基类（abstract base class）
// 继承体系中最根本的类
//
// 我们会间接利用“指向抽象基类”的 pointer 或 reference 来操作系统中的各个对象，
// 而不直接操作各个实际对象。
//
//						LibMat (抽象基类)
//						  |
//		 -----------------------------------------
//		 |			|				|			 |
//		Book	ChildToys		Magazines		Files
//		 |
//	-------------------------------
//	|				|			  |
//	RentalBook	AudioBook		CDIBook
//
//	void loan_check_in(LibMat &mat){
//		mat.check_in();
//		// ...
//	}
//
//	程序中并不存在 LibMat 对象，多态的特征：mat 总是指向（代表）LibMat 的某个
//	派生对象，且只有在程序执行时才能确定具体对象，这就是动态绑定（Dynamic binding）
//	---------------------------------------------------------------------
//
//	默认情况下， member function 的决议程序(resolution)皆在编译时期静态地进行。
//	若要令其在执行期动态进行，我们就得在它的声明式前加上 virtual
//	静态成员函数无法被声明为 virtual
//
//	每个虚拟函数，要么得有其定义，要么可设为“纯”虚拟函数(pure virtual function)
//	如果对于该类而言，这个虚拟函数并无实质意义，将虚拟函数赋值为 0，意思是令它
//	为一个“纯”虚拟函数。
//	virtual void gen_elems(int pos) = 0;
//
//	任何类如果声明有一个或多个纯虚拟函数，那么，由于其接口的不完整性（纯虚拟
//	函数没有函数定义，是谓不完整），程序无法为它产生任何对象。这种类只能作为
//	派生类的子对象之用，且这些派生类必须为所有的虚拟函数提供确切的定义
//	-------------------------------------------------------------------------
//
//	根据一般规则，凡基类定义有一个或多个虚拟函数，应该要将其 destructor 声明
//	为 virtual，像这样：
//	class ClassA{
//	public:
//		virtual ~ClassA(){}
//		virtual void fun1(){// ...}
//		void fun2(){// ...}
//		// ...
//	}
//
//	为什么？
//
//	class SubClassA : public ClassA{
//	public:
//		void fun1(){// ...}
//		void fun3(){// ...}
//		// ...
//	}
//
//	ClassA *ps = new SubClassA;
//	delete ps;
//
//	ps 是基类的指针，但它指向派生类对象，当 delete 表达式施行于该指针时，
//	destructor 会先施行于指针所指的对象身上，于是将此对象占用的内存空间释放；
//	于是， ps 调用的 destructor 一定是 SubClassA 的 destructor，不是 ClassA
//	的 destructor，而此决议操作应该在执行期进行。
//
//	ps->fun1() // ok 通过虚拟函数机制
//	ps->fun2() // ok 通过继承机制
//	ps->fun3() // error
//
//	派生类并不一定要指定关键字 virtual，但函数原型必须吻合
//	-------------------------------------------------------------------------
//
//	在两种情况下，虚拟函数机制不会出现预期行为：
//	1）在基类的 constructor 和 destructor 内；
//	2）当我们使用的是基类的对象，而非基类对象的 pointer 或 reference 时。
//
//	void print(LibMat object,
//			   const LibMat *pointer,
//			   const LibMat &reference){
//		object.print(); // 必定调用 LibMat::print();
//		pointer->pointer; // 通过虚拟函数机制进行决议
//		reference.pointer; // 通过虚拟函数机制进行决议
//	}
//  --------------------------------------------------------------------------
//
//  执行期识别机制（Run-Time Type Identification ----- RTTI）
//  由程序语言支持，让我们得以查询多态化的 class pointer 或 class reference
//  获得其所指对象的实际型别
//
//  #include <typeinfo>
//
//	SubClassA sub;
//  ClassA *ps = &sub;
//  if(typeid(*ps) == typeid(sub)){
//		ps->fun1(); // ok，且调用派生类 fun1()
//		ps->SubClassA::fun1(); // error，ps 并非一个 SubClassA 指针，
//							   // 虽然它现在的确指向某个 SubClassA 对象
//	}
//
//  if(typeid(*ps) == typeid(sub)){
//		SubClassA *pt = static_cast<SubClassA*>(ps); // 无条件转换
//		pt->fun1(); // ok，且调用派生类 fun1()
//		pt->fun3(); // ok
//	}
//	
//	dynamic_cast 会在执行期检验操作
//	上述功能也可这样：
//
//	if(SubClassA *pt = dynamic_cast<SubClassA*>(ps)){
//		pt->fun1()
//		// ...
//	}
//
