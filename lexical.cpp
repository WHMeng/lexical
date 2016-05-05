#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <map>
#include <ctype.h>
#define TOKEN_SIZE 1000
using namespace std;

typedef pair<int, int> mpair; // 分别为单词种别和单词自身的值

map<string, mpair> flag_table; // 标识符表
map<string, mpair> num_table; // 数字表
map<string, mpair> str_table; // 字符串表

// 可自行添加关键字或操作符，后续代码作相应修改
const char *KEY_WORDS[] = {"main", "int", "char", "if", "else", "for", "while", "return", "void"};
const char *OPERATORS[] = {"=", "+", "-", "*", "/", "(", ")", "[", "]", "{", "}", ",", ":", ";", ">", "<", ">=", "<=", "==", "\""};
int mark_key[10];
int mark_ope[50];
// 间距
int width1 = 15;
int width2 = 7;
int width3 = 7;

// 是否为关键字
int iskey(char *str)
{
	int i;
	int len = sizeof(KEY_WORDS) / sizeof(char *);
	for(i = 0; i < len; i++){
		if(!strcmp(KEY_WORDS[i], str)){
			return i;
		}
	}
	return -1;
}

// 是否为操作符
int isope(char *str)
{
	int i;
	int len = sizeof(OPERATORS) / sizeof(char *);
	for(i = 0; i < len; i++){
		if(!strcmp(OPERATORS[i], str)){
			return i;
		}
	}
	return -1;
}

// 获取关键字或标识符
void get_keyorid(char *token, char *ptr, FILE *fp)
{
	while(isalnum(*ptr)){
		*++ptr = fgetc(fp);
	}
	ungetc(*ptr, fp);
	*ptr = '\0';
	int flag = iskey(token);
	if(flag != -1){ // 是关键字
		if(!mark_key[flag])
			mark_key[flag] = 1;
		cout<< "  " << left << setw(width1) << token << setw(width2) << flag + 1 << setw(width3) << flag + 1 << endl;
	}
	else{ // 是标识符
		string s = "";
		map<string, mpair>::iterator it;
		s.append(token);
		it = flag_table.find(s);
		mpair mp;
		if(it == flag_table.end()){ // 标识符不在符号表里
			mp = make_pair(10, flag_table.size() + 1);
			flag_table[s] = mp;
		}
		else{
			it = flag_table.find(s);
			mp = it->second;
		}
		string sub;
		if(s.length() > width1 - 1){ // 字符串太长，为显示方便截断后面的串
			sub = s.substr(0, width1 - 4);
			sub.append("...");
		}
		else
			sub = s;
		cout<< "  " << left << setw(width1) << sub << setw(width2) << mp.first << setw(width3) << mp.second << endl;
	}
}

// 获取数字
void get_number(char *token, char *ptr, FILE *fp)
{
	while(isdigit(*ptr)){
		*++ptr = fgetc(fp);
	}
	ungetc(*ptr, fp);
	*ptr = '\0';
	map<string, mpair>::iterator it;
	string num;
	num.append(token);
	it = num_table.find(num);
	mpair mp;
	if(it == num_table.end()){
		mp = make_pair(20, num_table.size() + 1);
		num_table[num] = mp;
	}
	else{
		it = num_table.find(num);
		mp = it->second;
	}
	string sub;
	if(num.length() > width1 - 1){
		sub = num.substr(0, width1 - 4);
		sub.append("...");
	}
	else
		sub = num;
	cout<< "  " << left << setw(width1) << sub << setw(width2) << mp.first << setw(width3) << mp.second << endl;
}

// 判断是否为字符串
void try_string(char *token, char *ptr, FILE *fp)
{
	*++ptr = fgetc(fp);
	while(!feof(fp) && *ptr != '"'){
		*++ptr = fgetc(fp);
	}
	if(!feof(fp)) // 还没读到文件尾
		*++ptr = '\0';
	else // 已经读到文件尾
		*ptr = '\0';
	string s = "", sub;
	s.append(token);
	if(s.size() > width1 - 1){
		sub = s.substr(0, width1 - 4);
		sub.append("...");
	}
	else
		sub = s;
	if(*(ptr-1) == '"'){ // 找到匹配的 "
		map<string, mpair>::iterator it;
		it = str_table.find(s);
		mpair mp;
		if(it == str_table.end()){
			mp = make_pair(50, str_table.size() + 1);
			str_table[s] = mp;
		}
		else{
			it = str_table.find(s);
			mp = it->second;
		}
		cout<< "  " << left << setw(width1) << sub << setw(width2) << mp.first << setw(width3) << mp.second  << endl;
	}
	else{ // 找不到匹配的 "
		int i;
		int len = strlen(token);
		for(i = 0; i < len - 1; i++)
			ungetc(*--ptr, fp);
		cout<< "  " << left << setw(width1) << sub << setw(width2) << "error!, miss terminal '\"'" << endl;
	}
}

void try_double_ope(char *token, char *ptr, FILE *fp)
{
	*++ptr = fgetc(fp);
	*++ptr = '\0';
	int sub = isope(token);
	if(sub != -1)
		mark_ope[sub] = 1;
	else{
		ungetc(*--ptr, fp);
		*ptr = '\0';
		sub = isope(token);
		mark_ope[sub] = 1;
	}
	cout<< "  " << left << setw(width1) << token << setw(width2) << sub + 21 << setw(width3) << sub + 21 << endl;
}

void try_single_ope(char *token, char *ptr, FILE *fp)
{
	*++ptr = '\0';
	int sub = isope(token);
	if(sub != -1){
		mark_ope[sub] = 1;
		cout<< "  " << left << setw(width1) << token << setw(width2) << sub + 21 << setw(width3) << sub + 21 << endl;
	}
	else{
		if(token[0] < 0 || token[0] > 127) // 非 ASCII 码
			token[0] = '?';
		cout<< "  " << left << setw(width1) << token << "error" << endl;
	}
}

// 判断一个串
void judge_str(char ch, FILE *fp)
{
	char token[TOKEN_SIZE];
	char *ptr = token;
	*ptr = ch;
	if(isalpha(*ptr)){ // token 以字母开头
		get_keyorid(token, ptr, fp); // 判断是关键字或标识符
	}
	else if(isdigit(*ptr)){ // token 以数字开头
		get_number(token, ptr, fp); // 判断是数字
	}
	else if(*ptr == '"'){ // token 以 " 开头
		try_string(token, ptr, fp); // 可能是字符串
	}
	else if(*ptr == '>' || *ptr == '<' || *ptr == '='){ // 可能是双目操作符
		try_double_ope(token, ptr, fp);
	}
	else{
		try_single_ope(token, ptr, fp); //可能是单目操作符
	}
}

int main()
{
	FILE *fp = fopen("in.txt", "r");
	if(fp == NULL){
		perror("in.txt open failed\n");
		return 1;
	}
	cout << "\n  " << left << setw(width1) << "STRING" << setw(width2) << "KINDS" << setw(width3) << "SELFWORD" << endl;
	printf("  --------------------------------------\n");
	char ch = fgetc(fp);
	while(!feof(fp)){
		if(ch != ' ' && ch != '\t' && ch != '\n'){
			judge_str(ch, fp);
		}
		ch = fgetc(fp);
	}
	fclose(fp);
	return 0;
}
