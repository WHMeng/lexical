//
// (18) 让接口容易被正确使用，不易被误用
//      Make interfaces easy to use correctly and hard to use incorrectly
//
// ------------------------------------------------------------------------
// (19) 设计 class 犹如设计 type
//      Treat class design as type design
//
//      设计 class 前应该考虑的问题：
//      --新 type 的对象应该如何被创建和销毁？
//      --对象的初始化和对象的赋值该有什么样的差别？ // 条款 4
//      --新 type 的对象如果被以值传递，意味着什么？
//      --什么是新 type 的“合法值”
//      --你的新 type 需要配合某个继承图系吗？
//      --你的新 type 需要什么样的转换？
//      --什么样的操作符和函数对此新 type 而言是合理的？
//      --什么样的标准函数应该驳回（即你必须声明为 private）
//      --谁该取用新 type 的成员？
//      --什么是新 type 的“未声明接口”
//      --你的新 type 有多么一般化？
//      --你真的需要一个新 type 吗？
//
// ------------------------------------------------------------------------
// (20) 宁以 pass-by-reference-to-const 替换 pass-by-value
//      Prefer pass-by-reference-to-const to pass-by-value
//
//      class Window{
//      public:
//			...
//			std::string name() const;
//			virtual void display() const;
//      };
//
//      class WindowWithScrollBars : public Window{
//      public:
//			...
//			virtual void display() const;
//      };
//
//      void printNameAndDisplay(Window w){ // 不正确，参数可能被切割
//			std::cout << w.name();
//			w.display();
//      }
//
//      WindowWithScrollBars wwsb;
//      printNameAndDisplay(wwsb); // 将调用 Window::display
//
//      void printNameAndDisplay(const Window &w){ // ok
//			std::cout << w.name();
//			w.display();
//      }
//
// -----------------------------------------------------------------------
// (21) 必须返回对象时，别妄想返回其 reference
//      Don't try to return a reference when you must return an object
//
//		const Rational &operator*(const Rational &lhs, const Rational &rhs){
//			static Rational result;
//			result = ...;
//			return result;
//		}
//
//		bool operator==(const Rational &lhs, const Rational &rhs);
//
//	 	Rational a, b, c, d;
//		if((a * b) == (c * d)) ...
//
//		上面 if 语句总为 true
//		等价形式：
// 
//		if(operator==(operator*(a, b), operator*(c, d)));
//
//		每个 operator* 调用都返回一个 reference 指向 operator* 内部定义的
//		static Rational 对象
//
// -----------------------------------------------------------------------
// (22) 将成员变量声明为 private
//      Declare data members private
//
// -----------------------------------------------------------------------
// (23) 宁以 non-member,non-friend 替换 member 函数
//      Prefer non-member non-friend functions to member functions
//
//      class WebBrowser{
//		public:
//			...
//			void clearCache();
//			void clearHistory();
//			void clearCookies();
//			...
//      };
//
//      要批量执行上述函数操作，可以这样：
//
//      class WebBrowser{
//		public:
//			...
//			void clearEverything();
//			...
//		};
//
//		也可以这样：
//
//		void clearBrowser(WebBrowser &wb){
//			wb.clearCache();
//			wb.clearHistory();
//			wb.clearCookies();
//		}
//
//		愈多的函数可以访问数据，数据的封装性愈低，因此上述功能实现中，后者
//		封装性更好（无法访问 private 成员）
//
//		比较自然的做法：
//
//		namespace WebBrowserStuff{
//			class WebBrowser{...};
//			void clearBrowser(WebBrowser &wb);
//			...
//		}
//
// ----------------------------------------------------------------------
// (24) 若所有参数皆需类型转换，请为此采用 non-member 函数
//      Declare non-member functions when type conversions should apply to
//      all parameters
//
//      class Rational{
//      public:
//			Rational(int n = 0, int d = 1);
//			...
//			const Rational operator*(const Rational &rhs) const;
//      };
//
//      Rational E(1, 8);
//      Rational H(1, 2);
//      Rational result = E * H; // ok
//      result = H * 2; // ok
//      result = 2 * H; // error
//
//      相当于
//
//      result = H.operator*(2); // ok
//      result = 2.operator*(H); // error 
//
//      只有当参数被列于参数列内，这个参数才是隐式类型转换的合格参与者
//
//      解决办法
//
//      const Rational operator*(const Rational &lhs, const Rational &rhs){
//			return Rational(lsh.get_n() * rhs.get_n(),
//			                lsh.get_d() * rhs.get_d());
//      }
//
//      result = H * 2; // ok
//      result = 2 * H; // ok
//
// -----------------------------------------------------------------------
// (25) 考虑写出一个不抛异常的 swap 函数
//      Consider support for a non-throwing swap
//      -- 待完善
//
// ------------------------------------------------------------------------
// (26) 尽可能延后变量定义式的出现时间
//      Postpone variable definitions as long as possible
//
// (27) 尽量少做转型动作
//      Minimize casting
//
//      C 风格转型
//      (T)expression
//      T(expression)
//
//      C++ 加入的 4 种新式转型
//      const_cast<T>(expression) // 通常用于移除对象 const 性
//      dynamic_cast<T>(expression)
//      reinterpret_cast<T>(expression)
//      static_cast<T>(expression)
//
//      class Window{
//		public:
//			virtual void onResize() {...}
//			...
//      };
//      
//      错误的写法：
//      class SpecialWindow : public Window{
//      public:
//			virtual void onResize() {
//				static_cast<Window>(*this).onResize();
//				...
//			}
//      };
//
//      正确的写法：
//      class SpecialWindow : public Window{
//      public:
//			virtual void onResize() {
//				Window::onResize(); // 通过调用 Window::onResize 作用在
//				                       *this 身上
//				...
//			}
//      };
//
//		之所以需要 dynamic_cast，通常是因为你想在一个你认定为 derived class
//		对象身上执行 derived class 操作函数，但你的手上却只有一个“指向 base”
//		的 pinter 或者 reference，你只能靠它们来处理对象。有两个一般性做法
//		可以避免这个问题
//
//      class Window {...}
//      class SpecialWindow : public Window{
//      public:
//			void blink();
//			...
//      };
//
//      typedef
//      std::vector<std::tr1::shared_ptr<Window> > VPW;
//      VPW winPtrs;
//      for(VPW::iterator iter = winPtrs.begin();
//			iter != winPters.end(); ++iter){
//			if(SpecialWindow *psw = dynamic_cast<SpecialWindow *>(iter->
//			get()))
//			psw->blink();
//		} // 不希望这样用 dynamic_cast
//
//		应该改成这样：
//      typedef
//      std::vector<std::tr1::shared_ptr<Window> > VPSW;
//      VPSW winPtrs;
//      for(VPW::iterator iter = winPtrs.begin();
//			iter != winPters.end(); ++iter){
//			(*iter)->blink();
//		}
//
//		另一种方法：
//		class Window{
//		public:
//			virtual void blink() {}
//			...
//		};
//
//		class SpecialWindow : public Window{
//		public:
//			virtual void blink() {...}
//			...
//		};
//
//      typedef
//      std::vector<std::tr1::shared_ptr<Window> > VPSW;
//      VPSW winPtrs;
//      for(VPW::iterator iter = winPtrs.begin();
//			iter != winPters.end(); ++iter){
//			(*iter)->blink();
//		}
//
// -------------------------------------------------------------------
// (28) 避免返回 handles 指向对象内部成分
//      Avoid returning "handles" to object internals
//
//      class Point{
//      public:
//			Point(int x, int y);
//			...
//			void setX(int newVal);
//			void setY(int newVal);
//			...
//      };
//
//      struct RectData{
//			Point ulhc; // upper left-hand corner
//			Point lrhc; // lower right-hand corner
//      };
//
//      class Rectangle{
//      public:
//			const point &upperLeft() const {return pData->ulhc;};
//			const point &lowerRight() const {return pData->lrhc;};
//			...
//		private:
//			std::tr1::shared_ptr<RectData> pData;
//      };
//
//      class GUIObject {...};
//      const Rectangle
//			boundingBox(const GUIObject &obj);
//
//		GUIObject *pgo;
//		...
//		const Point *pUpperLeft = 
//			*(boundingBox(*pgo).upperLeft());
//
//		boundingBox() 的调用产生一个临时对象，而 upperLeft() 返回该对象的引用；这个语句
//		执行后，临时对象将被销毁，此时 pUpperLeft 将变成空悬指针(dangling pointer)
// 
//
//
//
//
