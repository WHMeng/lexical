#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <deque>
#include <iomanip>
#include <map>
#include <string>
#include <iostream>
#define STRSIZE 2000
using namespace std;
typedef pair<char, string> pairG;
typedef pair<int, char> paira;

typedef struct{
	int state;
	char ch;
}Elem;

deque<Elem> dq;

map<int, pairG> G;
map<paira, string> ACTION;
map<paira, int> GOTO;

int step;

void init_G()
{
	pairG pg;
	pg = make_pair('E', "E+T");
	G[1] = pg;
	pg = make_pair('E', "T");
	G[2] = pg;
	pg = make_pair('T', "T*F");
	G[3] = pg;
	pg = make_pair('T', "F");
	G[4] = pg;
	pg = make_pair('F', "(E)");
	G[5] = pg;
	pg = make_pair('F', "i");
	G[6] = pg;
}

void init_ACTION()
{
	paira pa;
	pa = make_pair(0, 'i');
	ACTION[pa] = "s5";
	pa = make_pair(0, '(');
	ACTION[pa] = "s4";
	pa = make_pair(1, '+');
	ACTION[pa] = "s6";
	pa = make_pair(1, '#');
	ACTION[pa] = "acc";
	pa = make_pair(2, '+');
	ACTION[pa] = "r2";
	pa = make_pair(2, '*');
	ACTION[pa] = "s7";
	pa = make_pair(2, ')');
	ACTION[pa] = "r2";
	pa = make_pair(2, '#');
	ACTION[pa] = "r2";
	pa = make_pair(3, '+');
	ACTION[pa] = "r4";
	pa = make_pair(3, '*');
	ACTION[pa] = "r4";
	pa = make_pair(3, ')');
	ACTION[pa] = "r4";
	pa = make_pair(3, '#');
	ACTION[pa] = "r4";
	pa = make_pair(4, 'i');
	ACTION[pa] = "s5";
	pa = make_pair(4, '(');
	ACTION[pa] = "s4";
	pa = make_pair(5, '+');
	ACTION[pa] = "r6";
	pa = make_pair(5, '*');
	ACTION[pa] = "r6";
	pa = make_pair(5, ')');
	ACTION[pa] = "r6";
	pa = make_pair(5, '#');
	ACTION[pa] = "r6";
	pa = make_pair(6, 'i');
	ACTION[pa] = "s5";
	pa = make_pair(6, '(');
	ACTION[pa] = "s4";
	pa = make_pair(7, 'i');
	ACTION[pa] = "s5";
	pa = make_pair(7, '(');
	ACTION[pa] = "s4";
	pa = make_pair(8, '+');
	ACTION[pa] = "s6";
	pa = make_pair(8, ')');
	ACTION[pa] = "s11";
	pa = make_pair(9, '+');
	ACTION[pa] = "r1";
	pa = make_pair(9, '*');
	ACTION[pa] = "s7";
	pa = make_pair(9, ')');
	ACTION[pa] = "r1";
	pa = make_pair(9, '#');
	ACTION[pa] = "r1";
	pa = make_pair(10, '+');
	ACTION[pa] = "r3";
	pa = make_pair(10, '*');
	ACTION[pa] = "r3";
	pa = make_pair(10, ')');
	ACTION[pa] = "r3";
	pa = make_pair(10, '#');
	ACTION[pa] = "r3";
	pa = make_pair(11, '+');
	ACTION[pa] = "r5";
	pa = make_pair(11, '*');
	ACTION[pa] = "r5";
	pa = make_pair(11, ')');
	ACTION[pa] = "r5";
	pa = make_pair(11, '#');
	ACTION[pa] = "r5";
}

void init_GOTO()
{
	paira pa;
	pa = make_pair(0, 'E');
	GOTO[pa] = 1;
	pa = make_pair(0, 'T');
	GOTO[pa] = 2;
	pa = make_pair(0, 'F');
	GOTO[pa] = 3;
	pa = make_pair(4, 'E');
	GOTO[pa] = 8;
	pa = make_pair(4, 'T');
	GOTO[pa] = 2;
	pa = make_pair(4, 'F');
	GOTO[pa] = 3;
	pa = make_pair(6, 'T');
	GOTO[pa] = 9;
	pa = make_pair(6, 'F');
	GOTO[pa] = 3;
	pa = make_pair(7, 'F');
	GOTO[pa] = 10;
}

void print_cur(char *str, int cur)
{
	char buf1[100];
	char buf2[100];
	buf1[0] = '\0';
	buf2[0] = '\0';
	int width1 = 6;
	int width2 = 15;
	int width3 = 15;
	int width4 = 15;
	static int flag = 0;
	if(!flag){
		cout << left << setw(width1) << "STEP" << setw(width2) << "STATE_STACK" << setw(width3) 
			<< "CHAR_STACK" << right << setw(width4) << "INPUT_STRING" << endl;
		cout << "----------------------------------------------------------" << endl;
		flag = 1;
	}
	cout << left << setw(width1) << ++step;
	int sz = dq.size();
	for(int i = sz-1; i >= 0; i--){
		sprintf(buf1+strlen(buf1), "%d ", dq[i].state);
		sprintf(buf2+strlen(buf2), "%c", dq[i].ch);
	}
	cout << left << setw(width2) << buf1 << setw(width3) << buf2 << right << setw(width4) << str+cur << endl;
}

void work(char *str)
{
	int i;
	int len = strlen(str);
	Elem ele;
	ele.state = 0;
	ele.ch = '#';
	dq.push_front(ele); // 初始状态入栈
	for(i = 0; i < len;){
		print_cur(str, i);
		char a = str[i];
		ele = dq.front();

		paira pa;
		pa = make_pair(ele.state, a);
		map<paira, string>:: iterator it1;
		it1 = ACTION.find(pa);
		if(it1 != ACTION.end()){
			string X = it1->second;
			if(X[0] == 's'){
				Elem nele;
				const char *p = X.c_str();
				nele.state = atoi(p+1);
				nele.ch = a;
				dq.push_front(nele); // [s, a] 入栈
				i++;
			}
			else if(X[0] == 'r'){
				const char *p = X.c_str();
				int val = atoi(p+1);
				pairG pg;
				pg = G[val];
				int len = pg.second.length();
				for(int j = 0; j < len; j++){ // 出栈
					dq.pop_front();
				}
				Elem e = dq.front();
				paira pa;
				pa = make_pair(e.state, pg.first);
				map<paira, int>:: iterator it2;
				it2 = GOTO.find(pa);
				if(it2 != GOTO.end()){
					Elem et;
					et.state = it2->second;
					et.ch = pg.first; // 规约
					dq.push_front(et);
				}
				else{
					printf("GOTO error!\n");
					return;
				}
			}
			else if(X[0] == 'a'){
				printf("acc\n");
				return;
			}
		}
		else{
			printf("ACTION error!\n");
			return;
		}
	}
}

int main()
{
	char str[STRSIZE];
	printf("input the string end by #:\n");
	scanf("%s", str);
	init_G();
	init_ACTION();
	init_GOTO();
	work(str);
	return 0;
}
