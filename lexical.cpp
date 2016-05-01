#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <map>
#include <ctype.h>
#define TOKEN_SIZE 1000
using namespace std;

typedef pair<int, int> mpair;

map<string, mpair> flag_table;
map<int, mpair> num_table;

const char *KEY_WORDS[] = {"main", "int", "char", "if", "else", "for", "while", "return", "void"};
const char *OPERATORS[] = {"=", "+", "-", "*", "/", "(", ")", "[", "]", "{", "}", ",", ":", ";", ">", "<", ">=", "<=", "=="};
int mark_key[10];
int mark_ope[50];

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

int judge_str(char ch, FILE *fp)
{
	char token[TOKEN_SIZE];
	char *ptr = token;
	*ptr = ch;
	if(isalpha(*ptr)){
		while(isalnum(*ptr)){
			*++ptr = fgetc(fp);
		}
		ungetc(*ptr, fp);
		*ptr = '\0';
		int flag = iskey(token);
		if(flag != -1){
			if(!mark_key[flag])
				mark_key[flag] = 1;
		}
		else{
			string s = "";
			map<string, mpair>::iterator it;
			s.append(token);
			it = flag_table.find(s);
			if(it == flag_table.end()){
				mpair mp;
				mp = make_pair(10, flag_table.size() + 1);
				flag_table[s] = mp;
			}
		}
		return 1;
	}
	else if(isdigit(*ptr)){
		while(isdigit(*ptr)){
			*++ptr = fgetc(fp);
		}
		ungetc(*ptr, fp);
		*ptr = '\0';
		map<int, mpair>::iterator it;
		int num = atoi(token);
		it = num_table.find(num);
		if(it == num_table.end()){
			mpair mp;
			mp = make_pair(20, num_table.size() + 1);
			num_table[num] = mp;
		}
		return 1;
	}
	else if(*ptr == '>' || *ptr == '<' || *ptr == '='){
		*++ptr = fgetc(fp);
		*++ptr = '\0';
		int sub = isope(token);
		if(sub != -1)
			mark_ope[sub] = 1;
		else{
			ungetc(*--ptr, fp);
			*ptr = '\0';
			mark_ope[isope(token)] = 1;
		}
		return 1;
	}
	else{
		*++ptr = '\0';
		int sub = isope(token);
		if(sub != -1){
			mark_ope[sub] = 1;
			return 1;
		}
		else return 0;
	}
}

void print_list()
{
	printf("\n  -- KEY_WORDS --\n");
	printf("  ---------------\n");
	int i;
	int lenk = sizeof(KEY_WORDS)/sizeof(char *);
	int leno = sizeof(OPERATORS)/sizeof(char *);
	for(i = 0; i < lenk; i++){
		if(mark_key[i]){
			printf("  %-10s%-5d%-5d\n", KEY_WORDS[i], i + 1, i + 1);
		}
	}
	printf("\n  -- OPERATORS --\n");
	printf("  ---------------\n");
	for(i = 0; i < leno; i++){
		if(mark_ope[i]){
			printf("  %-10s%-5d%-5d\n", OPERATORS[i], i + 21, i + 21);
		}
	}
	printf("\n  -- IDENTITIERS --\n");
	printf("  -----------------\n");
	map<string, mpair>::iterator it1;
	for(it1 = flag_table.begin(); it1 != flag_table.end(); it1++){
		mpair mp = it1->second;
		cout<< "  " << left << setw(10) << it1->first << setw(5) << mp.first << setw(5) << mp.second << endl;
	}
	printf("\n  -- NUMBERS --\n");
	printf("  -------------\n");
	map<int, mpair>::iterator it2;
	for(it2 = num_table.begin(); it2 != num_table.end(); it2++){
		mpair mp = it2->second;
		cout<< "  " << left << setw(10) << it2->first << setw(5) << mp.first << setw(5) << mp.second << endl;
	}
}

int main()
{
	FILE *fp = fopen("in.txt", "r");
	if(fp == NULL){
		perror("in.txt open failed\n");
		return 1;
	}
	char ch = fgetc(fp);
	while(!feof(fp)){
		if(ch != ' ' && ch != '\t' && ch != '\n'){
			judge_str(ch, fp);
		}
		ch = fgetc(fp);
	}
	print_list();
	return 0;
}
