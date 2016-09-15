//
// (13) 以对象管理资源
//      Use objects to manage resources
//
//      int fun(){
//			Object *p = new Object("aaa");
//			...
//			delete p;
//      }
//
//      如果在 ... 之中函数被返回，则造成内存泄漏
//
//      int fun(){
//			std::auto_ptr<Object> p(new Object("aaa")); // #include <memory>
//			...
//      }
//
//      只要对象离开作用域，p 的析构函数将释放对象资源
//      但是 auto_ptr(智能指针) 不支持赋值操作，即不会有两个 auto_ptr 同时指向同一个
//      对象，如果这样做了，则原 auto_ptr 将变成 null
//
//      int fun(){
//			std::tr1::shared_ptr<Object> p(new Object("aaa")); // #include <tr1/memory>
//			...
//      }
//
//      有良好的赋值行为，可被 STL 所用
//
//      auto_ptr 和 tr1::shared_ptr 两者都在其析构函数内做 delete 而不是
//      delete []，所以在动态分配得到的 array 上使用 auto_ptr 或 tr1::
//      shared_ptr 不是个好主意，尽管可以通过编译
//
//      资源取得时机便是初始化时机
//      RAII(Resource Acquisition Is Initialization)
//
//      为防止资源泄漏，请使用 RAII 对象，它们在构造函数中获得资源并在析构
//      函数中释放资源
//
// -----------------------------------------------------------------------
// (14) 在资源管理类中小心 coping 行为
//      Think carefully about copying behavior in resource-managing classes
//
//      复制 RAII 对象必须一并复制它所管理的资源，所以资源的 copying 行为
//      决定 RAII 对象的 copying 行为
//
//      普遍常见的 RAII class copying 行为是：抑制 copying、施行引用计数法
//
// -----------------------------------------------------------------------
// (15) 在资源管理类中提供对原始资源的访问
//      Provide access to raw resources in resoure-managing classes
//
//      显式转换
//
//      std:tr1::shared_ptr<Object> p(new Object);
//      int fun(const Object *p);
//      int x = fun(p); // error!
//      int x = fun(p.get()); // ok，传递的是 p 内的原始指针
//
//      隐式转换
//
//      class Investment{
//      public:
//			bool isTexFree() const;
//			...
//      };
//      Investment *createInvestment();
//      std::tr1::shared_ptr<Investment> pi1(createInvestment());
//      bool taxable1 = !(pi1->isTexFree()); // ok, operator->
//      ...
//      std::auto_ptr<Investment> pi2(createInvestment());
//      bool taxable2 = !((*pi2).isTexFree()); // ok, operator*
//
//      另一种隐式转换
//
//      void changeFontSize(FontHandle f);
//
//      class Font{
//      public:
//			...
//			operator FontHandle() const{ // 隐式转换函数
//				return f;
//			}
//		private:
//			FontHandle f;
//      };
//
//      Font f;
//      changeFontSize(f); // 将 Font 隐式转换为 FontHandle
//
//      但这个隐式转换会增加错误发生机会，例如可能在需要 Font 时意外
//      创建一个 FontHandle
//
//      Font f1;
//      FontHandle f2 = f1; // 原意是要拷贝一个 Font 对象
//							// 却反而将 f1 隐式转换为底部的 FontHandle
//							// 然后才复制它
//
// ----------------------------------------------------------------------
// (16) 成对使用 new 和 delete 时要采取相同形式
//      Use the same form in corresponding uses of new and delete
//
//      注意：
//      typedef std::string AddressLines[4]; // 每个人的地址有 4 行
//                                           // 每行是一个 string
//      std::string *pal = new AddressLines; // 返回 string*，就像
//                                           // new string[4] 一样
//      delete pal; // error, 行为未定义
//      delete [] pal; // ok
// 
// -----------------------------------------------------------------------
// (17) 以独立语句将 newed 对象置入智能指针
//      Store newed objects in smart pointers in standalone statements
//
//      int priority();
//      void processWidget(std::tr1::shared_ptr<Widget>pw, int priority);
//
//      processWidget(new Widget, priority()); // error
//
//      tr1::shared_ptr 构造函数需要一个原始指针(raw pointer)，但该构造函数
//      是个 explicit 构造函数，无法进行隐式转换
//
//      processWidget(std::tr1::shared_ptr<Widget>(new Widget), priority()); // ok 
//
//      但可能造成泄漏资源
//      std::tr1::shared_ptr<Widget> pw(new Widget);
//      processWidget(pw, priority()); // ok
//
//
//
