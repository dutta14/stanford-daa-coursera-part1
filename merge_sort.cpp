/*
Program to perform merge sort on an array of elements
and find the number of inversions in the array.
*/
#include <iostream>
using namespace std;

void merge(int *a, int start, int mid, int end, long long *count) {
	int i = start, j = mid + 1;
	int *c = new int[end - start];
	int k = 0;
	while (i <= mid && j <= end) {
		if (a[i] < a[j])
			c[k++] = a[i++];
		else {
			c[k++] = a[j++];
			*count += (mid - i + 1);
		}
	}
	while (i <= mid) {
		c[k++] = a[i++];
	}
	while (j <= end) {
		c[k++] = a[j++];
	}
	k = 0;
	for (i = start; i <= end; i++)
		a[i] = c[k++];
}

void merge_sort(int *a, int start, int end, long long *count) {
	if (start < end) {
		int mid = (start + end) / 2;
		merge_sort(a, start, mid, count);
		merge_sort(a, mid+1, end, count);
		merge(a, start, mid, end, count);
	}
}

int main() {

	int n;
	cout << "Enter n: ";
	cin >> n;
	int *a = new int[n];
	cout << "Enter numbers: ";
	int i;
	for (i = 0; i < n; i++)
		cin >> a[i];

	long long c = 0;
	long long *count = &c;
	merge_sort(a, 0, n-1, count);

	cout << "Inversions: " << *count;
	cout << endl;
	int x;
	cin >> x;
	return 0;
}