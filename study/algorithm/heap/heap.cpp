#include <iostream>
#include <vector>
using namespace std;

class Heap{ // 大根堆
public:
	Heap() : inf(0x7fffffff), m_data(1, inf) {}
	void push(int val);
	void pop();
	void show();
	int size();
private:
	void swap(int &v1, int &v2);
private:
	const int inf;
	vector<int> m_data;
};

int Heap::size(){
	return m_data.size() - 1;
}

void Heap::swap(int &v1, int &v2){
	int tmp = v1;
	v1 = v2;
	v2 = tmp;
}

void Heap::push(int val){
	m_data.push_back(val);
	int cur = size();
	while(cur >> 1){
		int fa = (cur >> 1);
		if(m_data[cur] > m_data[fa]){
			swap(m_data[cur], m_data[fa]);
			cur = fa;
		}else break;
	}
}

void Heap::pop(){
	int len = size(); 
	if(len < 1)
		return;
	m_data[1] = m_data[len];
	m_data.pop_back();
	int cur = 1;
	while(cur <= size()){
		int left = (cur<<1);
		int right = (cur<<1|1);
		int big = cur;
		if(left <= size() && m_data[left] > m_data[big]){
			big = left;
		}
		if(right <= size() && m_data[right] > m_data[big]){
			big = right;
		}
		if(big != cur){
			swap(m_data[big], m_data[cur]);
			cur = big;
		}else{
			break;
		}
	}
}

void Heap::show(){
	cout << "elements: " << endl;
	for(auto val : m_data){
		cout << val << " ";
	}
	cout << endl;
}

int main(){
	Heap heap;
	int arr[] = {8, 5, 2, 10, 3, 1, 4, 6};
	for(auto val : arr){
		heap.push(val);
	}
	heap.show();
	int len = heap.size();
	for(int i = 0; i < len; i++){
		heap.pop();
		heap.show();
	}
	return 0;
}
