//
// 指针高级声明：
//
// UNIX 系统 + Internet 可以获得一个叫 cdecl 的程序，它可以在 C 语言的声明
// 和英语之间进行转换，它可以解释一个现存的 C 语言声明：
// ---------------------------------------------------------------------
// 
// 函数指针：
//
// int f(int);
// int (*pf)(int) = &f; // & 是可选的
//
// int ans;
// ans = f(25); // ok
// ans = (*pf)(25); // ok
// ans = pf(25); // ok
// ---------------------------------------------------------------------
//
// 回调函数：
//
// 用户把一个函数指针作为参数传递给其他函数，后者将“回调”用户的函数。
//
// // 类型无关链表查找：
//
// int compare_ints(void const *a, void const *b){
//     if(*(int *)a == *(int *)b)
//         return 0;
//     else
//         return 1;
// }
//
// Node *search_list(Node *node, void const *value,
//			int (*compare)(void const *, void const *)){
//     while(node != NULL){
//	       if(compare(&node->value, value) == 0)
//		       break;
//		   node = node->link;
//     }
//     return node;
// }
//
// // 然后可以这样调用：
// desired_node = search_list(root, &desired_value, compare_ints);
//
// // 如果希望在字符串链表中进行查找，可以这样：
// #include <string.h>
// desired_node = search_list(root, "desired_value", strcmp);
// ----------------------------------------------------------------------
//
// 转移表（函数指针数组）：
//
// 看一个计算器的部分实现：
// switch(oper){
// case ADD:
//         result = add(op1, op2);
//         break;
// case SUB:
//         result = sub(op1, op2);
//         break;
// case MUL:
//         result = mul(op1, op2);
//         break;
// case DIV:
//         result = div(op1, op2);
//         break;
// // ...
// }
//
// 如果计算器有上百个操作符，switch 语句将非常长~
//
// 创建转移表步骤：
// 1）声明函数原型；
// 2）声明并初始化函数指针数组。
//
// double add(double, double);
// double sub(double, double);
// double mul(double, double);
// double div(double, double);
// ...
//
// double (*oper_func[])(double, double) = {
//     add, sub, mul, div, ...
// };
//  
// 这样，下面语句可以代替前面的整条 switch 语句！
// result = oper_func[oper](op1, op2);
// ----------------------------------------------------------------------
//
// 字符串常量:
//
// 当一个字符串常量出现于表达式中时，它的值是个指针常量，指向第一个字符
//
// "xyz" + 1; // 将返回指向字符 'y' 的指针
// *"xyz"; // 该表达式的值是字符 'x';
// "xyz"[2] // 该表达式的值是字符 'z';
//
//
