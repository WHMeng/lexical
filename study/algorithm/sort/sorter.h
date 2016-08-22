#ifndef SORTER_H
#define SORTER_H

#if 0
quick_sort(arr, l, r) [l, r]
1.	if(l >= r) 
2.		return;
4.	base = arr[r];
5.	for(i = l-1, j = l; j < r; j++){
6.		if(arr[j] <= base){
7.			i++;
8.			swap(arr[j], arr[i]);
9.		}
10.	}
11.	swap(arr[i+1], arr[r]);
12.	quick_sort(arr, l, i);
13.	quick_sort(arr, l+2, r);

quick_sort_nonrecursive(arr, l, r) [l, r]
1.	p.left = l;
2.	p.right = r;
3.	stack.push(p);
4.	while(!stack.empty){
5.		p = stack.top;
6.		stack.pop;
7.		l = p.left;
8.		r = p.right;
9.		if(l >= r) continue;
10.		base = arr[r];
11.		for(i = l-1, j = l; j < r; j++){
12.			if(arr[j] <= base){
13.				i++;
14.				swap(arr[j], arr[i]);
15.			}
16.		}
17.		swap(arr[i+1], arr[r]);
18.		p.left = i + 2; p.right = r;
19.		stack.push(p);
20.		p.left = l; p.right = i;
21.		stack.push(p);
22.	}

insertion_sort(arr, len)
1.	for(i = 1; i < len; i++){
2.		temp = arr[i];
3.		for(j = i-1; j >= 0 && arr[j] > temp; j--)
4.			arr[j+1] = arr[j];
5.		arr[j+1] = temp;
6.	}

shell_sort(arr, len)
1.	for(gap = len>>1; gap > 0; gap >>= 1)
2.		for(i = gap; i < len; i++){
3.			temp = arr[i];
4.			for(j = i-gap; j >= 0 && arr[i] > temp; j -= gap)
5.				arr[j+gap] = arr[j];
6.			arr[j+gap] = temp;
7.		}

selection_sort(arr, len)
1.	for(i = 0; i < len-1; i++){
2.		min = i;
3.		for(j = i+1; j < len; j++)
4.			if(arr[min] > arr[j])
5.				min = j;
6.		temp = arr[min];
7.		arr[min] = arr[i];
8.		arr[i] = temp;
9.	}

merge_sort(arr, tar, l, r) [l, r)
1.	if(l >= r - 1)
2.		return;
3.	mid = l + (r - l) / 2;
4.	merge_sort(arr, tar, l, mid);
5.	merge_sort(arr, tar, mid, r);
6.	i = p = l; q = mid;
7.	while(p < mid && q < r)
8.		tar[i++] = arr[p] < arr[q] ? arr[p++] : arr[q++];
9.	while(p < mid)
10.		tar[i++] = arr[p++];
11.	while(q < r)
12.		tar[i++] = arr[q++];
13.	for(i = l; i < r; i++)
14.		arr[i] = tar[i];

merge_sort_nonrecursive(arr, n)
1.	for(len = 1; len < n; len <<= 1){
2.		for(l = 0; l < n; l += 2*len){
3.			mid = min(l+len, n);
4.			r = min(l+2*len, n);
5.			k = p = l; q = mid;
6.			while(p < mid && q < r)
7.				tar[k++] = arr[p] < arr[q] ? arr[p++] : arr[q++];
8.			while(p < mid)
9.				tar[k++] = arr[p++];
10.			while(q < r)
11.				tar[k++] = arr[q++];
12.		}
13.		for(i = 0; i < n; i++)
14.			arr[i] = tar[i];
15.	}

counting_sort(arr, n) // arr 为正整数序列
1.	for(i = 0; i < m; i++) // m 为 arr 的数据范围 
2.		count_arr[i] = 0;
3.	for(i = 0; i < n; i++)
4.		count_arr[arr[i]]++;
5.	for(i = 1; i < m; i++)
6.		count_arr[i] += count_arr[i-1];
7.	for(i = n-1; i >= 0; i--)
8.		sorted_arr[--count_arr[arr[i]]] = arr[i];
9.	for(i = 0; i < n; i++)
10.		arr[i] = sorted_arr[i];

radix_sort(arr, n) // arr 为正整数序列
1.	BASE = 10;
2.	m = max_in(arr);
3.	exp = 1;
4.	while(m / exp > 0){
5.		for(i = 0; i < BASE; i++)
6.			bucket[i] = 0;
7.		for(i = 0; i < n; i++)
8.			bucket[(a[i]/exp)%BASE]++;
9.		for(i = 1; i < BASE; i++)
10.			bucket[i] += bucket[i-1];
11.		for(i = n-1; i >= 0; i--)
12.			b[--bucket[(a[i]/exp)%BASE]] = a[i];
13.		for(i = 0; i < n; i++)
14.			arr[i] = b[i];
15.		exp *= BASE;
16.	}
#endif

#endif
