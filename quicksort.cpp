/*
Program to sort the elements of an array using quick sort.
*/
#include <iostream>
#include <fstream>
using namespace std;

int pivot(int *a, int l, int r) {
	return rand() % (r + 1 - l) + l;
}

int partition(int *a, int l, int r) {
	int index = pivot(a, l, r);
	swap(a[index], a[l]);
	int p = a[l];
	int i = l + 1;
	for (int j = l + 1; j <=r; j++) {
		if (a[j] < p) {
			swap(a[j], a[i]);
			i++;
		}
	}
	swap(a[l], a[i - 1]);
	return i - 1;
}

void quicksort(int *a, int l, int r) {
	if (l < r) {
		int p = partition(a, l, r);
		quicksort(a, l, p - 1);
		quicksort(a, p + 1, r);
	}
}

int main() {
	ifstream fp;
	fp.open("Text.txt");
	int n;
	fp >> n;
	int *a = new int[n];
	for (int i = 0; i < n; i++)
		fp >> a[i];
	quicksort(a, 0, n - 1);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}