// 
// -----------------------------------------------------------------
// (1) 视 C++ 为一个语言联邦 
//     View C++ as a federation of languages
//
// -----------------------------------------------------------------
// (2) 尽量以 const, enum, inline 替换 #define
//     Prefer consts, enums, and inlines to #define
//
//     class GamePlayer{
//	   private:
//		   enum {NumTurns = 5};
//		   int scores[NumTurns];
//     };
//
// -----------------------------------------------------------------
// (3) 尽可能使用 const
//     Use const whenever posiible
//
//	   std::vector<int> vec;
//	   ...
//     const std::vector<int>::iterator iter = vec.begin();
//     *iter = 10; // ok
//     ++iter // error
//
//     std::vector<int>::const_iterator cIter = vec.begin();
//     *cIter = 10; // error
//     ++cIter // ok 
//
//     当 const 和 non-const 成员函数有着实质等价实现时，在 non-const 调
//     用 const 实现 non-const 版本以避免代码重复（但是会影响美观）
//
//     class TextBlock(){
//     public:
//         ...
//         const char &operator[](std::size_t position) const{
//             ... // 边界检测
//             ... // 标记数据
//             ... // 各种操作
//             return text[position];
//         }
//         char &operator[](std::size_t position){
//             ... // 边界检测
//             ... // 标记数据
//             ... // 各种操作
//             return text[position];
//         }
//     private:
//	       std::string text;
//     };
//     
//     修改后：
//
//     class TextBlock(){
//     public:
//         ...
//         const char &operator[](std::size_t position) const{
//             ... // 边界检测
//             ... // 标记数据
//             ... // 各种操作
//             return text[position];
//         }
//         char &operator[](std::size_t position){
//             return
//             const_cast<char &>(
//                 static_cast<const TextBlock &>(*this)[position];
//             )
//         }
//     private:
//	       std::string text;
//     };
//
//     注意不能反向用，即不能在 const 调用 non-const 版本实现 const
//
// ---------------------------------------------------------------------
// (4) 确定对象被使用前已先被初始化
//     Make sure that objects are initialized before they're used
//
//     C++ 规定，对象的成员变量的初始化动作发生在进入构造函数本体之前。在
//     类的构造函数内的操作不是初始化，而是赋值。这种情况对内置类型不为真
//
//     class Test{
//     public:
//         Test(const std::string &name){
//             _name = name; // 这是赋值，而非初始化
//             _num = 0;
//         }
//     private:
//         std::string _name;
//         int _num;
//     };
//
//     一个更好的写法是使用成员初始化列
//
//     Test(const std::string &name)
//     : _name(name), // 这是初始化
//       _num(0) // 内置类型初始化与赋值代价相同
//     {
//     }
//
//     这种写法通常效率更高
//     另外需要注意 C++ 有十分固定的“成员初始化次序”。即使它们在成员初始化
//     列中以不同次序出现（合法），也不会有任何影响。
//
//
//     static 对象，其寿命从被构造出来直到程序结束为止，这种对象包括 global
//     对象、定义于 namespace 作用域内的对象、在 classes 内、函数内、以及
//     在 file 作用域内被声明为 static 的对象。其中在函数内的 static 对象
//     成为 local static 对象（因为它们对于函数而言是 local），其他 static
//     对象称为 non-local static 对象
//
//     编译单元指产出单一目标文件的那些源码，基本是它是单一源码文件及其含
//     入的头文件
//
//     C++ 对“定义于不同的编译单元内的 non-local static 对象”的初始化相对
//     次序并无明确定义。可用 reference-returning 函数防止这类问题
//
//     任何一种 non-const static 对象，不论是 local 或 non-local，在多线
//     程环境下“等待某事发生”都会有麻烦。
//
