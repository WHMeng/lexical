//
// 锯齿状数组：字符串指针数组
//
// char *turnip[UMPTEEN];
// char my_string[] = "your memseage here";
// turnip[i] = &my_string[0]; // 共享字符串
// turnip[j] = malloc(strlen(my_string)+1);
// strcpy(turnip[j], my_string); // 拷贝字符串
// ---------------------------------------------------------------------
//
// 数组和指针参数是如何被编译器修改的：
//
// 实参                  所匹配的形参
// char c[8][10];        char(*c)[10]; // 数组指针
// char *c[15];          char **c;
// char (*c)[64];        char (*c)[64];
// char **c;             char **c;
//
// 以下都是合法的：
//
// my_function_1(int fruit[2][3][5]){;}
// my_function_2(int fruit[][3][5]){;}
// my_function_3(int (*fruit)[3][5]){;}
//
// int apricot[2][3][5];
// int (*p)[3][5] = apricot;
// int (*q)[2][3][5] = &apricot;
//
// my_function_1(apricot);
// my_function_2(apricot);
// my_function_3(apricot);

// my_function_1(p);
// my_function_2(p);
// my_function_3(p);
//
// my_function_1(*q);
// my_function_2(*q);
// my_function_3(*q);
// ----------------------------------------------------------------------	
//
// 使用指针从函数返回一个数组
//
// int (*paf())[20]{ // paf 是一个函数，返回一个指向包含 20 个 int 元素的数组的指针
//     int (*pear)[20]; // 声明一个指向包含 20 个 int 元素的数组的指针
//     pear = calloc(20, sizeof(int));
//     if(!pear) longjmp(error, 1);
//     return pear;
// }
//
// 可以这样调用：
// int (*res)[20];
// res = paf();
// (*res)[3] = 12;
