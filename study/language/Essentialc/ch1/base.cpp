#if 0

#include <fstream>

ofstream outfile("out.txt"); // 定义供输出用的 file stream 对象
                             // 会覆盖原有内容
ofstream outfile("out.txt", ios_base::app);
                             // 在原有内容前提下追加
if(!outfile) // 判断是否开启成功

cerr // 无缓冲标准输出

ifstream infile("in.txt"); // 定义供读取用的 file stream 对象

fstream iofile("iofile.txt", ios_base::in|ios_base::app);
                           // 同时读写同一个文件

#endif
