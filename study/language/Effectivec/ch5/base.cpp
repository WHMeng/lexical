//
// (32) 确定你的 public 继承塑膜出 is-a 关系
//      Make sure public inheritance models "is-a"
//
//      class D : public B
//
//      每一个 D 对象都是一个 B 对象，反之如果你需要一个 D 对象，B 对象
//      无法效劳
//
//      class Student : public Person {...};
//
//      void eat(const Person &p);
//      void study(const Student &s);
//      Person p;
//      Student s;
//      eat(p); // ok
//      eat(s); // ok
//      study(s); // ok
//      study(p); // error
//
//      上述论点只对 public 继承才成立
//
// (33) 避免遮掩继承而来的名称
//      Avoid hiding inheited names
//
//      class Base{
//		private:
//			int x;
//		public:
//			virtual void mf1() = 0;
//			virtual void mf1(int);
//			virtual void mf2();
//			void mf3();
//			void mf3(double);
//			...
//      };
//
//      class Derived : public Base{
//      public:
//			virtual void mf1();
//			void mf3();
//			void mf4();
//			...
//      };
//
//      Derived d;
//      int x;
//      ...
//      d.mf1(); // ok
//      d.mf1(x); // error
//      d.mf2(); // ok
//      d.mf3(); // ok
//      d.mf3(x); // error
//
//      可以做这样的修改
//
//      class Derived : public Base{
//      public:
//			using Base::mf1; // 让 Base class 内名为 mf1 的所有东西
//			using Base::mf3 // 在 Derived 作用域内都可见（并且 public）
//			virtual void mf1(); 
//			void mf3();
//			void mf4();
//			...
//      };
//
//      这样就能正常继承
//
//
//
//
//
//
//
