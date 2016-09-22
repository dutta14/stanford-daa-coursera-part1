/*
Program to find the ith order statistic of an array.
*/
#include <iostream>
using namespace std;

int pivot(int *a, int l, int r) {
	return rand() % (r + 1 - l) + l;
}

int partition(int *a, int l, int r) {
	int index = pivot(a, l, r);
	int p = a[index];// a[l];
	swap(a[index], a[l]);
	int i = l + 1;
	for (int j = l + 1; j <= r; j++) {
		if (a[j] < p) {
			swap(a[i], a[j]);
			i++;
		}
	}
	swap(a[l], a[i - 1]);
	return i - 1;
}

int findorder(int *a, int l, int r, int i) {
	if (l < r) {
		int p = partition(a, l, r);
		if (p == i)
			return a[p];
		if (p > i)
			return findorder(a, l, p - 1, i);
		else
			return findorder(a, p + 1, r, i);
	}
	return a[l];
}

int main() {
	int n;
	cin >> n;
	int *a = new int[n];
	for (int j = 0; j < n; j++)
		cin >> a[j];
	int i;
	cin >> i;
	int v = findorder(a, 0, n - 1, i);
	cout << v;
	
	return 0;
}