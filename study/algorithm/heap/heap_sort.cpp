#include <iostream>
using namespace std;

void adjust_heap(int arr[], int n, int k){
	int cur = k;
	while(cur < n){
		int left = ((cur+1)<<1) - 1;
		int right = ((cur+1)<<1|1) - 1;
		int big = cur;
		if(left < n && arr[left] > arr[big])
			big = left;
		if(right < n && arr[right] > arr[big])
			big = right;
		if(big != cur){
			int tmp = arr[cur];
			arr[cur] = arr[big];
			arr[big] = tmp;
			cur = big;
		}else{
			break;
		}
	}
}

void build_max_heap(int arr[], int n){
	for(int i=n/2; i > 0; i--){
		adjust_heap(arr, n, i-1);
	}
}

void show(int arr[], int n){
	printf("elements:\n");
	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void heap_sort(int arr[], int n){
	build_max_heap(arr, n);
	for(int i = n-1; i > 0; i--){
		int tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;
		n -= 1;
		adjust_heap(arr, n, 0);
	}
}

int main(){
	int arr[] = {3, -2, 6, 4, 5, 7, 5, 8, 1, 9, 0};
	heap_sort(arr, 11);
	show(arr, 11);
	return 0;
}
