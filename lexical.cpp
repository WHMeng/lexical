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
map<string, mpair> num_table;
map<string, mpair> str_table;

const char *KEY_WORDS[] = {"main", "int", "char", "if", "else", "for", "while", "return", "void"};
const char *OPERATORS[] = {"=", "+", "-", "*", "/", "(", ")", "[", "]", "{", "}", ",", ":", ";", ">", "<", ">=", "<=", "==", "\""};
int mark_key[10];
int mark_ope[50];
int width_l = 15;

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

void get_identif(char *token, char *ptr, FILE *fp)
{
	while(isalnum(*ptr)){
		*++ptr = fgetc(fp);
	}
	ungetc(*ptr, fp);
	*ptr = '\0';
	int flag = iskey(token);
	if(flag != -1){
		if(!mark_key[flag])
			mark_key[flag] = 1;
		cout<< "  " << left << setw(width_l) << token << setw(width_l) << flag + 1 << setw(width_l) << flag + 1 << endl;
	}
	else{
		string s = "";
		map<string, mpair>::iterator it;
		s.append(token);
		it = flag_table.find(s);
		mpair mp;
		if(it == flag_table.end()){
			mp = make_pair(10, flag_table.size() + 1);
			flag_table[s] = mp;
		}
		else{
			it = flag_table.find(s);
			mp = it->second;
		}
		string sub;
		if(s.length() > width_l - 1){
			sub = s.substr(0, width_l - 4);
			sub.append("...");
		}
		else
			sub = s;
		cout<< "  " << left << setw(width_l) << sub << setw(width_l) << mp.first << setw(width_l) << mp.second << endl;
	}
}

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
	if(num.length() > width_l - 1){
		sub = num.substr(0, width_l - 4);
		sub.append("...");
	}
	else
		sub = num;
	cout<< "  " << left << setw(width_l) << sub << setw(width_l) << mp.first << setw(width_l) << mp.second << endl;
}

void try_string(char *token, char *ptr, FILE *fp)
{
	*++ptr = fgetc(fp);
	while(!feof(fp) && (*ptr != '"')){
		*++ptr = fgetc(fp);
	}
	if(!feof(fp))
		*++ptr = '\0';
	else
		*ptr = '\0';
	string s = "", sub;
	s.append(token);
	if(s.size() > width_l - 1){
		sub = s.substr(0, width_l - 4);
		sub.append("...");
	}
	else
		sub = s;
	if(*(ptr-1) == '"'){
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
		cout<< "  " << left << setw(width_l) << sub << setw(width_l) << mp.first << setw(width_l) << mp.second  << endl;
	}
	else{
		int i;
		int len = strlen(token);
		for(i = 0; i < len - 1; i++)
			ungetc(*--ptr, fp);
		cout<< "  " << left << setw(width_l) << sub << setw(width_l) << "error!, miss terminal '\"'" << endl;
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
	cout<< "  " << left << setw(width_l) << token << setw(width_l) << sub + 21 << setw(width_l) << sub + 21 << endl;
}

void try_single_ope(char *token, char *ptr, FILE *fp)
{
	*++ptr = '\0';
	int sub = isope(token);
	if(sub != -1){
		mark_ope[sub] = 1;
		cout<< "  " << left << setw(width_l) << token << setw(width_l) << sub + 21 << setw(width_l) << sub + 21 << endl;
	}
	else{
		cout<< "  " << left << setw(width_l) << token << "error" << endl;
	}
}

void judge_str(char ch, FILE *fp)
{
	char token[TOKEN_SIZE];
	char *ptr = token;
	*ptr = ch;
	if(isalpha(*ptr)){
		get_identif(token, ptr, fp);
	}
	else if(isdigit(*ptr)){
		get_number(token, ptr, fp);
	}
	else if(*ptr == '"'){
		try_string(token, ptr, fp);
	}
	else if(*ptr == '>' || *ptr == '<' || *ptr == '='){
		try_double_ope(token, ptr, fp);
	}
	else{
		try_single_ope(token, ptr, fp);
	}
}

int main()
{
	FILE *fp = fopen("in.txt", "r");
	if(fp == NULL){
		perror("in.txt open failed\n");
		return 1;
	}
	cout << "\n  " << left << setw(width_l) << "STRING" << setw(width_l) << "KINDS" << setw(width_l) << "SELFWORD" << endl;
	printf("  --------------------------------------\n");
	char ch = fgetc(fp);
	while(!feof(fp)){
		if(ch != ' ' && ch != '\t' && ch != '\n'){
			judge_str(ch, fp);
		}
		ch = fgetc(fp);
	}
	return 0;
}
